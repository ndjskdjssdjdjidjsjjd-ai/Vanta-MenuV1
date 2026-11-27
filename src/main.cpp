#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>

#include <array>
#include <cstdio>
#include <sstream>
#include <string>

using namespace geode::prelude;

namespace {
constexpr std::array<char const*, 100> PANEL_NAMES = {
    "Mod name",
    "Developer credit",
    "Mod version",
    "Mod identifier",
    "Geometry Dash target",
    "Geode target",
    "Compatibility reminder",
    "Supported platforms",
    "Build metadata",
    "Feature count",
    "Dashboard summary",
    "Selected row count",
    "Enabled row count",
    "Disabled row count",
    "Dashboard category list",
    "Dashboard help",
    "Empty selection note",
    "Settings navigation hint",
    "Dashboard footer",
    "Dashboard version note",
    "Compact layout note",
    "Large text note",
    "Contrast note",
    "Reduced motion note",
    "Touch layout note",
    "Keyboard navigation note",
    "Label style note",
    "Section spacing note",
    "Button placement note",
    "Text wrapping note",
    "Readable labels",
    "High contrast guidance",
    "Motion guidance",
    "Color-independent status",
    "Short label guidance",
    "Screen reader label note",
    "Input focus note",
    "Touch target note",
    "Clear state text",
    "Accessibility scope",
    "Main menu access",
    "Dashboard action",
    "Settings action",
    "Geode settings path",
    "Mods page hint",
    "Panel grouping",
    "Back button guidance",
    "Close button guidance",
    "Menu button label",
    "Navigation scope",
    "Game version status",
    "Geode version status",
    "Mod load status",
    "Configuration status",
    "Selected panels status",
    "Menu entry status",
    "Build target status",
    "Dependency status",
    "Local-only status",
    "Diagnostic limitations",
    "Local settings",
    "No telemetry",
    "No network requests",
    "No account access",
    "No save editing",
    "No file scanning",
    "Local configuration scope",
    "Data reset guidance",
    "Privacy summary",
    "Offline mode",
    "CMake project",
    "Geode SDK requirement",
    "Windows build",
    "Android build",
    "GitHub Actions",
    "Build artifact note",
    "Install guidance",
    "Versioning note",
    "Source layout",
    "Release checklist",
    "No gameplay changes",
    "No physics changes",
    "No timing changes",
    "No unlock changes",
    "No bypasses",
    "No automation",
    "Read-only diagnostics",
    "Interface-only options",
    "Single-player safe scope",
    "Safe feature summary",
    "Getting started",
    "Configuration help",
    "Compatibility help",
    "Build help",
    "Issue reporting",
    "Maintainer attribution",
    "Project source",
    "Changelog note",
    "Open source note",
    "Vanta safety scope",
};

std::string settingKey(size_t index) {
    char key[16];
    std::snprintf(key, sizeof(key), "feature_%03zu", index + 1);
    return key;
}
} // namespace

class $modify(VantaMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto* menu = CCMenu::create();
        if (!menu) {
            return true;
        }
        menu->setPosition(CCPointZero);

        auto* dashboardLabel = CCLabelBMFont::create("VANTA", "goldFont.fnt");
        auto* settingsLabel = CCLabelBMFont::create("SET", "goldFont.fnt");
        if (!dashboardLabel || !settingsLabel) {
            return true;
        }

        auto* dashboardButton = CCMenuItemSpriteExtra::create(
            dashboardLabel, this, menu_selector(VantaMenuLayer::onDashboard)
        );
        auto* settingsButton = CCMenuItemSpriteExtra::create(
            settingsLabel, this, menu_selector(VantaMenuLayer::onSettings)
        );
        if (!dashboardButton || !settingsButton) {
            return true;
        }

        dashboardLabel->setScale(0.55f);
        settingsLabel->setScale(0.55f);

        auto const winSize = CCDirector::sharedDirector()->getWinSize();
        dashboardButton->setPosition({winSize.width - 44.f, winSize.height - 40.f});
        settingsButton->setPosition({winSize.width - 44.f, winSize.height - 64.f});

        menu->addChild(dashboardButton);
        menu->addChild(settingsButton);
        this->addChild(menu, 1000);
        return true;
    }

    void onDashboard(CCObject*) {
        std::ostringstream body;
        size_t enabled = 0;
        size_t listed = 0;

        for (size_t i = 0; i < PANEL_NAMES.size(); ++i) {
            auto const key = settingKey(i);
            if (!Mod::get()->getSettingValue<bool>(key)) {
                continue;
            }

            ++enabled;
            if (listed < 12) {
                body << "- " << PANEL_NAMES[i] << "\n";
                ++listed;
            }
        }

        if (enabled == 0) {
            body << "No dashboard rows are selected.\n";
            body << "Use the SET button to choose which local information to show.";
        } else {
            body << "\n" << enabled << " of " << PANEL_NAMES.size()
                 << " dashboard rows are enabled.";
            if (enabled > listed) {
                body << "\nUse SET to review the remaining "
                     << (enabled - listed) << " selected rows.";
            }
        }

        FLAlertLayer::create("VantaMenuV1", body.str(), "Close")->show();
    }

    void onSettings(CCObject*) {
        geode::openSettingsPopup(Mod::get());
    }
};
