#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include <dlfcn.h>
#include <filesystem>
#include <cmath>
using namespace std;
namespace fs = filesystem;

// ===== PLUGIN INTERFACE =====

// Base plugin interface
class Plugin {
public:
    virtual ~Plugin() = default;
    virtual string getName() const = 0;
    virtual string getVersion() const = 0;
    virtual void execute() = 0;
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
};

// Plugin factory function type
using PluginFactory = Plugin* (*)();
using PluginDestroyer = void (*)(Plugin*);

// ===== PLUGIN MANAGER =====

class PluginManager {
private:
    unordered_map<string, void*> loadedLibraries;
    unordered_map<string, unique_ptr<Plugin>> loadedPlugins;
    vector<string> pluginDirectories;

public:
    PluginManager() {
        // Add default plugin directories
        pluginDirectories.push_back("./plugins");
        pluginDirectories.push_back("../plugins");
    }

    ~PluginManager() {
        unloadAllPlugins();
    }

    // Add a directory to search for plugins
    void addPluginDirectory(const string& dir) {
        pluginDirectories.push_back(dir);
    }

    // Get plugin directories (for demonstration)
    const vector<string>& getPluginDirectories() const {
        return pluginDirectories;
    }

    // Load a plugin from a shared library
    bool loadPlugin(const string& pluginName) {
        // Check if already loaded
        if (loadedPlugins.find(pluginName) != loadedPlugins.end()) {
            cout << "Plugin '" << pluginName << "' is already loaded." << endl;
            return true;
        }

        // Try to find the plugin library
        string libraryPath = findPluginLibrary(pluginName);
        if (libraryPath.empty()) {
            cout << "Could not find plugin library for '" << pluginName << "'" << endl;
            return false;
        }

        // Load the shared library
        void* library = dlopen(libraryPath.c_str(), RTLD_LAZY);
        if (!library) {
            cout << "Failed to load library '" << libraryPath << "': " << dlerror() << endl;
            return false;
        }

        // Clear any existing error
        dlerror();

        // Get the factory function
        PluginFactory factory = reinterpret_cast<PluginFactory>(dlsym(library, "createPlugin"));
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            cout << "Failed to find createPlugin function: " << dlsym_error << endl;
            dlclose(library);
            return false;
        }

        // Create the plugin instance
        Plugin* plugin = factory();
        if (!plugin) {
            cout << "Plugin factory returned null" << endl;
            dlclose(library);
            return false;
        }

        // Initialize the plugin
        if (!plugin->initialize()) {
            cout << "Plugin '" << pluginName << "' failed to initialize" << endl;
            delete plugin;
            dlclose(library);
            return false;
        }

        // Store the plugin and library
        loadedLibraries[pluginName] = library;
        loadedPlugins[pluginName] = unique_ptr<Plugin>(plugin);

        cout << "Successfully loaded plugin '" << pluginName << "' (" << plugin->getVersion() << ")" << endl;
        return true;
    }

    // Unload a plugin
    bool unloadPlugin(const string& pluginName) {
        auto pluginIt = loadedPlugins.find(pluginName);
        if (pluginIt == loadedPlugins.end()) {
            cout << "Plugin '" << pluginName << "' is not loaded." << endl;
            return false;
        }

        // Shutdown the plugin
        pluginIt->second->shutdown();

        // Remove from loaded plugins
        loadedPlugins.erase(pluginIt);

        // Unload the library
        auto libIt = loadedLibraries.find(pluginName);
        if (libIt != loadedLibraries.end()) {
            dlclose(libIt->second);
            loadedLibraries.erase(libIt);
        }

        cout << "Successfully unloaded plugin '" << pluginName << "'" << endl;
        return true;
    }

    // Unload all plugins
    void unloadAllPlugins() {
        for (auto& pair : loadedPlugins) {
            pair.second->shutdown();
        }
        loadedPlugins.clear();

        for (auto& pair : loadedLibraries) {
            dlclose(pair.second);
        }
        loadedLibraries.clear();
    }

    // Execute a plugin
    bool executePlugin(const string& pluginName) {
        auto it = loadedPlugins.find(pluginName);
        if (it == loadedPlugins.end()) {
            cout << "Plugin '" << pluginName << "' is not loaded." << endl;
            return false;
        }

        cout << "Executing plugin '" << pluginName << "'..." << endl;
        it->second->execute();
        return true;
    }

    // Get information about loaded plugins
    void listLoadedPlugins() const {
        cout << "Loaded plugins:" << endl;
        if (loadedPlugins.empty()) {
            cout << "  (none)" << endl;
            return;
        }

        for (const auto& pair : loadedPlugins) {
            cout << "  " << pair.first << " v" << pair.second->getVersion() << endl;
        }
    }

    // Get a plugin instance
    Plugin* getPlugin(const string& pluginName) {
        auto it = loadedPlugins.find(pluginName);
        return (it != loadedPlugins.end()) ? it->second.get() : nullptr;
    }

private:
    // Find the plugin library file
    string findPluginLibrary(const string& pluginName) {
        // Try different naming conventions
        vector<string> possibleNames = {
            "lib" + pluginName + ".so",
            pluginName + ".so",
            "lib" + pluginName + ".dylib",
            pluginName + ".dylib"
        };

        for (const string& dir : pluginDirectories) {
            for (const string& name : possibleNames) {
                string fullPath = dir + "/" + name;
                if (fs::exists(fullPath)) {
                    return fullPath;
                }
            }
        }

        return "";
    }
};

// ===== BUILT-IN PLUGINS =====

// Example plugin: Calculator
class CalculatorPlugin : public Plugin {
public:
    string getName() const override { return "Calculator"; }
    string getVersion() const override { return "1.0.0"; }

    bool initialize() override {
        cout << "Calculator plugin initialized" << endl;
        return true;
    }

    void shutdown() override {
        cout << "Calculator plugin shut down" << endl;
    }

    void execute() override {
        cout << "=== Calculator Plugin ===" << endl;
        cout << "2 + 3 = " << (2 + 3) << endl;
        cout << "10 * 5 = " << (10 * 5) << endl;
        cout << "100 / 4 = " << (100 / 4) << endl;
        cout << "sqrt(16) = " << sqrt(16) << endl;
    }
};

// Example plugin: Text Processor
class TextProcessorPlugin : public Plugin {
public:
    string getName() const override { return "TextProcessor"; }
    string getVersion() const override { return "1.1.0"; }

    bool initialize() override {
        cout << "Text Processor plugin initialized" << endl;
        return true;
    }

    void shutdown() override {
        cout << "Text Processor plugin shut down" << endl;
    }

    void execute() override {
        cout << "=== Text Processor Plugin ===" << endl;
        string text = "Hello, World!";
        cout << "Original: " << text << endl;
        cout << "Uppercase: " << toUpper(text) << endl;
        cout << "Reversed: " << reverse(text) << endl;
        cout << "Word count: " << countWords(text) << endl;
    }

private:
    string toUpper(const string& str) {
        string result = str;
        for (char& c : result) c = toupper(c);
        return result;
    }

    string reverse(const string& str) {
        return string(str.rbegin(), str.rend());
    }

    size_t countWords(const string& str) {
        size_t count = 0;
        bool inWord = false;
        for (char c : str) {
            if (isspace(c)) {
                inWord = false;
            } else if (!inWord) {
                inWord = true;
                count++;
            }
        }
        return count;
    }
};

// Example plugin: Data Analyzer
class DataAnalyzerPlugin : public Plugin {
public:
    string getName() const override { return "DataAnalyzer"; }
    string getVersion() const override { return "2.0.0"; }

    bool initialize() override {
        cout << "Data Analyzer plugin initialized" << endl;
        return true;
    }

    void shutdown() override {
        cout << "Data Analyzer plugin shut down" << endl;
    }

    void execute() override {
        cout << "=== Data Analyzer Plugin ===" << endl;
        vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        cout << "Data: ";
        for (int x : data) cout << x << " ";
        cout << endl;

        cout << "Sum: " << calculateSum(data) << endl;
        cout << "Average: " << calculateAverage(data) << endl;
        cout << "Median: " << calculateMedian(data) << endl;
        cout << "Standard Deviation: " << calculateStdDev(data) << endl;
    }

private:
    double calculateSum(const vector<int>& data) {
        double sum = 0;
        for (int x : data) sum += x;
        return sum;
    }

    double calculateAverage(const vector<int>& data) {
        return calculateSum(data) / data.size();
    }

    double calculateMedian(vector<int> data) {
        sort(data.begin(), data.end());
        size_t n = data.size();
        if (n % 2 == 0) {
            return (data[n/2 - 1] + data[n/2]) / 2.0;
        } else {
            return data[n/2];
        }
    }

    double calculateStdDev(const vector<int>& data) {
        double mean = calculateAverage(data);
        double sumSquares = 0;
        for (int x : data) {
            sumSquares += (x - mean) * (x - mean);
        }
        return sqrt(sumSquares / data.size());
    }
};

// ===== PLUGIN REGISTRY =====

// Plugin registry for built-in plugins
class PluginRegistry {
private:
    unordered_map<string, function<Plugin*()>> creators;

public:
    PluginRegistry() {
        // Register built-in plugins
        registerPlugin("Calculator", []() { return new CalculatorPlugin(); });
        registerPlugin("TextProcessor", []() { return new TextProcessorPlugin(); });
        registerPlugin("DataAnalyzer", []() { return new DataAnalyzerPlugin(); });
    }

    void registerPlugin(const string& name, function<Plugin*()> creator) {
        creators[name] = creator;
    }

    Plugin* createPlugin(const string& name) {
        auto it = creators.find(name);
        if (it != creators.end()) {
            return it->second();
        }
        return nullptr;
    }

    vector<string> getAvailablePlugins() const {
        vector<string> names;
        for (const auto& pair : creators) {
            names.push_back(pair.first);
        }
        return names;
    }
};

// ===== DEMONSTRATION =====

void demonstrateBuiltInPlugins() {
    cout << "=== Built-in Plugin System ===\n" << endl;

    PluginRegistry registry;

    cout << "Available plugins:" << endl;
    for (const string& name : registry.getAvailablePlugins()) {
        cout << "  " << name << endl;
    }
    cout << endl;

    // Create and use plugins directly
    vector<string> pluginNames = {"Calculator", "TextProcessor", "DataAnalyzer"};

    for (const string& name : pluginNames) {
        cout << "Creating plugin: " << name << endl;
        unique_ptr<Plugin> plugin(registry.createPlugin(name));

        if (plugin) {
            plugin->initialize();
            plugin->execute();
            plugin->shutdown();
        }
        cout << endl;
    }
}

void demonstrateDynamicPluginLoading() {
    cout << "=== Dynamic Plugin Loading ===\n" << endl;

    PluginManager manager;

    // Note: This would require actual shared library files to work
    // For demonstration, we'll show the interface

    cout << "Plugin Manager created" << endl;
    cout << "Plugin directories:" << endl;
    for (const string& dir : manager.getPluginDirectories()) {
        cout << "  " << dir << endl;
    }
    cout << endl;

    cout << "To use dynamic loading, you would:" << endl;
    cout << "1. Create shared library files (.so on Linux, .dylib on macOS)" << endl;
    cout << "2. Implement createPlugin() and destroyPlugin() functions" << endl;
    cout << "3. Export these functions from the shared library" << endl;
    cout << "4. Call manager.loadPlugin(\"pluginName\")" << endl;
    cout << endl;

    manager.listLoadedPlugins();
}

void demonstratePluginManager() {
    cout << "=== Plugin Manager with Built-in Plugins ===\n" << endl;

    PluginManager manager;
    PluginRegistry registry;

    // Simulate loading built-in plugins through the manager
    // (In a real system, these would be in separate shared libraries)

    cout << "Simulating plugin loading..." << endl;

    // For demonstration, we'll manually "load" the built-in plugins
    // In a real system, these would be loaded from shared libraries

    vector<string> pluginNames = {"Calculator", "TextProcessor", "DataAnalyzer"};

    for (const string& name : pluginNames) {
        cout << "Loading plugin: " << name << endl;
        // In a real implementation, this would load from a shared library
        // For now, we'll simulate it
        cout << "  (Simulated: Plugin '" << name << "' loaded successfully)" << endl;
    }
    cout << endl;

    cout << "Plugin management features:" << endl;
    cout << "• Dynamic loading/unloading of plugins" << endl;
    cout << "• Plugin lifecycle management (init/shutdown)" << endl;
    cout << "• Plugin discovery in multiple directories" << endl;
    cout << "• Error handling and reporting" << endl;
    cout << "• Memory management and cleanup" << endl;
}

// ===== PLUGIN DEVELOPMENT EXAMPLE =====

// Example of how to create a plugin (this would be in a separate file/library)
#if 0
// File: my_custom_plugin.cpp (compiled to libMyCustomPlugin.so)

#include "plugin_interface.h"

class MyCustomPlugin : public Plugin {
public:
    string getName() const override { return "MyCustomPlugin"; }
    string getVersion() const override { return "1.0.0"; }

    bool initialize() override {
        cout << "MyCustomPlugin initialized" << endl;
        return true;
    }

    void shutdown() override {
        cout << "MyCustomPlugin shut down" << endl;
    }

    void execute() override {
        cout << "Hello from MyCustomPlugin!" << endl;
        // Custom plugin logic here
    }
};

// Factory function (must be exported from shared library)
extern "C" Plugin* createPlugin() {
    return new MyCustomPlugin();
}

// Destroyer function (optional, for cleanup)
extern "C" void destroyPlugin(Plugin* plugin) {
    delete plugin;
}
#endif

int main() {
    cout << "=== C++ Plugin System Demo ===\n" << endl;

    demonstrateBuiltInPlugins();
    demonstrateDynamicPluginLoading();
    demonstratePluginManager();

    cout << "\n=== Plugin System Summary ===" << endl;
    cout << "• Plugin Interface: Common base class for all plugins" << endl;
    cout << "• Plugin Manager: Handles loading, unloading, and execution" << endl;
    cout << "• Dynamic Loading: Uses dlopen/dlsym for runtime loading" << endl;
    cout << "• Plugin Registry: Factory pattern for built-in plugins" << endl;
    cout << "• Lifecycle Management: Initialize/shutdown for proper resource handling" << endl;
    cout << "• Error Handling: Robust error reporting and recovery" << endl;
    cout << "• Extensibility: Easy to add new plugins without recompiling" << endl;

    return 0;
}