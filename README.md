# fmavlink

`fmavlink` 是一个自定义 MAVLink 协议维护仓库，面向飞控、地面站和其他上层项目提供统一的协议扩展能力。

这个仓库的核心职责是：

1. 用 YAML 维护自定义协议源。
2. 将 YAML 渲染为标准 MAVLink dialect XML。
3. 基于 `pymavlink` 生成 C / C++11 协议头文件。
4. 通过 `add_subdirectory` 的方式作为可复用子模块提供给其他工程使用。

库使用方不需要安装 Python。只有维护协议并重新生成产物时，才需要在仓库维护环境中执行生成脚本。

## 设计原则

- 易维护：协议源尽量简单直观，避免额外的复杂配置层。
- 可扩展：从一开始就支持后续新增多个自定义协议模块。
- 易接入：上游工程只需 `add_subdirectory` 并链接统一 target。
- 可追踪：协议源和生成结果都保存在仓库中，方便审查和回溯。

## 目录说明

- `protocols/fmavlink.yaml`：总协议入口，负责组织所有模块。
- `protocols/modules/*.yaml`：各个自定义协议模块。
- `protocols/modules/_template.yaml`：新增协议时可直接复制的模板。
- `generated/xml/`：渲染后的 MAVLink dialect XML。
- `generated/c/`：生成好的 C 协议头文件。
- `generated/cpp11/`：生成好的 C++11 协议头文件。
- `tools/generate.sh`：维护者刷新协议生成产物的统一入口。
- `tools/*.py`：协议校验、XML 渲染和代码生成脚本。
- `examples/`：最小接入示例。

## 协议维护规则

- 标识符使用英文，例如 `FM_BATTERY_STATUS`。
- `description` 可以直接写中文，方便维护和评审。
- 消息 ID 需要全仓唯一。
- 新增协议模块时：
  1. 在 `protocols/modules/` 下新增一个 YAML 文件。
  2. 可以直接复制 `_template.yaml` 后修改。
  3. 在 `protocols/fmavlink.yaml` 的 `modules` 列表里加入该文件名。
  4. 执行 `./tools/generate.sh` 刷新产物。

## 上游工程接入

上游工程直接这样使用：

```cmake
add_subdirectory(path/to/fmavlink)
target_link_libraries(your_target PRIVATE fmavlink)
```

`fmavlink` 对外只暴露一个统一 target。正常情况下，只需要链接它并包含：

```c
#include <fmavlink/mavlink.h>
```

如果需要 C++11 头文件：

```cmake
target_link_libraries(your_target PRIVATE fmavlink_cpp11)
```

仓库内部虽然保留了 `pymavlink` 生成的完整依赖头文件树，但这些都属于实现细节。对使用方来说，可以把它视为一个统一的自定义协议包。

## 维护者工作流

当 YAML 协议有变更时，由仓库维护者执行：

```bash
./tools/generate.sh
```

脚本会刷新以下内容：

- `generated/xml/fmavlink.xml`
- `generated/c/`
- `generated/cpp11/`

建议每次协议修改后都检查以下内容：

- 协议 YAML 是否符合预期
- 渲染后的 XML 是否正确
- 生成后的头文件是否更新
- 示例工程是否仍然可以正常编译

## Git 约定

以下内容会提交到 Git：

- 协议源 YAML
- 生成后的 XML
- 生成后的 C / C++11 头文件
- CMake、脚本、文档和示例

以下中间产物不会提交到 Git：

- `build/`
- `__pycache__/`
- `*.pyc`
- `generated/fmavlink.stamp`

## 示例

启用仓库内自带示例：

```bash
cmake -S . -B build -DFMAVLINK_BUILD_EXAMPLES=ON
cmake --build build
./build/examples/fmavlink_example
```
