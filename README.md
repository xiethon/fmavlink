# fmavlink

`fmavlink` 是一个自定义 MAVLink 协议维护仓库，面向飞控、地面站和其他上层项目提供统一的协议扩展能力。

这个仓库的核心职责是：

1. 用 YAML 维护自定义协议源。
2. 将 YAML 渲染为标准 MAVLink dialect XML。
3. 基于 `pymavlink` 生成 C / C++11 协议头文件。
4. 通过 `FetchContent` 的方式作为可复用依赖提供给其他工程使用。

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
- `description` 可以中文，方便维护。
- 消息 ID 需要全仓唯一。
- 新增协议模块时：
  1. 在 `protocols/modules/` 下新增一个 YAML 文件。
  2. 可以直接复制 `_template.yaml` 后修改。
  3. 在 `protocols/fmavlink.yaml` 的 `modules` 列表里加入该文件名。
  4. 执行 `./tools/generate.sh` 刷新产物。

## 上游工程接入

推荐使用 `FetchContent`：

```cmake
include(FetchContent)

FetchContent_Declare(
  fmavlink
  GIT_REPOSITORY git@github.com:xiethon/fmavlink.git
  GIT_TAG main
)

FetchContent_MakeAvailable(fmavlink)

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