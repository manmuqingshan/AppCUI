#include "AppCUI.hpp"

using namespace AppCUI;
using namespace AppCUI::Controls;
using namespace AppCUI::Dialogs;

struct WindowWithColors : public Dialogs::OnThemeChangedInterface
{
    Application::Config::CustomColorStorage colors;

    WindowWithColors()
    {
        const Graphics::ColorPair focused  = { Graphics::Color::Red, Graphics::Color::DarkBlue };
        const Graphics::ColorPair normal   = { Graphics::Color::Red, Graphics::Color::DarkBlue };
        const Graphics::ColorPair hovered  = { Graphics::Color::Yellow, Graphics::Color::DarkBlue };
        const Graphics::ColorPair inactive = { Graphics::Color::Gray, Graphics::Color::DarkBlue };
        const Graphics::ColorPair presset  = { Graphics::Color::Red, Graphics::Color::DarkBlue };

        auto colorObj = Graphics::ObjectColorState();
        colorObj.Set(focused, normal, inactive, hovered, presset);

        colors = {
            {
                  "A Custom SimpleColor",
                  { { "ColorPair1",
                      Graphics::CustomColor(Graphics::ColorPair{ Graphics::Color::Red, Graphics::Color::DarkBlue }) },
                    { "ColorPair2",
                      Graphics::CustomColor(
                            Graphics::ColorPair{ Graphics::Color::Green, Graphics::Color::DarkBlue }) } },
            },
            { "A Custom Object",
              { { "Obj1", Graphics::CustomColor(colorObj) },
                { "Obj2", Graphics::CustomColor(colorObj) } } }
        };

        if (!Dialogs::ThemeEditor::RegisterCustomColors(colors, this))
        {
            LOG_ERROR("Failed to register custom colors!");
            return;
        }
    }
    ~WindowWithColors() override
    {
        Dialogs::ThemeEditor::RemoveListener(this);
    }

    void OnThemeChanged(const Application::Config& config) override
    {
    }
};

int main()
{
    Log::ToFile("IniInitialization.log");
    if (!Application::Init())
        return 1;

    WindowWithColors colorsWindow = {};

    Application::GetDesktop()->Handlers()->OnStart = [](Reference<Control>) { Dialogs::ThemeEditor::Show(); };
    Application::Run();
    return 0;
}
