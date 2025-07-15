# DeepSeek Qt Plugin

A Qt plugin for integrating DeepSeek AI API into Qt applications.

## Features

- Easy integration with Qt applications
- Support for different DeepSeek models
- Simple API for sending prompts and receiving responses

## Requirements

- Qt 5.15 or later
- C++17 compatible compiler
- DeepSeek API key

## Building the Plugin

1. Make sure you have Qt and the necessary development tools installed.
2. Run the build script:

```bash
./build.sh
```

This will build both the plugin and the test application.

## Using the Plugin in Your Application

1. Include the plugin interface in your project:

```cpp
#include "deepseekinterface.h"
```

2. Load the plugin:

```cpp
QPluginLoader pluginLoader("path/to/libDeepSeekPlugin.so");
QObject *pluginInstance = pluginLoader.instance();
DeepSeekInterface *deepSeekPlugin = qobject_cast<DeepSeekInterface*>(pluginInstance);
```

3. Set your API key:

```cpp
deepSeekPlugin->setApiKey("your-api-key");
```

4. Send a prompt and get a response:

```cpp
QString response = deepSeekPlugin->sendPrompt("Your prompt here", "deepseek-chat");
```

## Test Application

A test application is included to demonstrate how to use the plugin. To run it:

```bash
./TestApp/build/TestApp
```

## Supported Models

- deepseek-chat
- deepseek-coder

## License

This project is licensed under the MIT License - see the LICENSE file for details.