# VantaMenuV1

VantaMenuV1 is a Geode utility mod by **kaizxfaq**. It adds `VANTA` and `SET` buttons to the Geometry Dash main menu. `VANTA` displays the dashboard rows you selected; `SET` opens the mod's Geode settings.

The settings contain **100 configurable dashboard rows** across ten groups. Each toggle controls whether that informational row appears in the local Vanta dashboard. The choices are saved by Geode.

## Safe scope

- Local interface and read-only information only.
- No gameplay, physics, timing, completion, unlock, or save-file changes.
- No automation, network requests, telemetry, or account access.

## Versions

- Mod version: `1.0.0`
- Geometry Dash target: `2.209`
- Geode SDK target: `v5.11.2`

Geode Launcher `1.9.1` is a launcher version, not the Geode SDK version used to compile a mod. Geode's v5.11.2 release notes mention fixes for 2.209 compatibility while noting that the release primarily targets 2.2081. Confirm the loader bundled with your launcher is compatible before installing. Geometry Dash `2.2091` is a separate target; this project does not claim support for it.

## Build locally

Install the Geode SDK and CMake, then set `GEODE_SDK` to the SDK directory:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
