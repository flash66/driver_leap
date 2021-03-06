#include "stdafx.h"
#include "CConfigHelper.h"
#include "Utils.h"

extern char g_ModuleFileName[];

bool CConfigHelper::ms_menu = true;
bool CConfigHelper::ms_applicationMenu = true;
bool CConfigHelper::ms_trigger = true;
bool CConfigHelper::ms_grip = true;
bool CConfigHelper::ms_touchpad = true;
bool CConfigHelper::ms_touchpadTouch = true;
bool CConfigHelper::ms_touchpadPress = true;
bool CConfigHelper::ms_touchpadAxes = true;
float CConfigHelper::ms_gripOffsetX = 0.f;
float CConfigHelper::ms_gripOffsetY = 0.f;
float CConfigHelper::ms_gripOffsetZ = 0.f;
bool CConfigHelper::ms_controllerLeftEnabled = true;
bool CConfigHelper::ms_controllerRightEnabled = true;

const std::vector<std::string> g_configAttributeTable
{
    "menu", "appMenu", "trigger", "grip",
    "touchpad", "touchpadTouch", "touchpadPress", "touchpadAxes",
    "gripOffsetX", "gripOffsetY", "gripOffsetZ",
    "leftEnabled", "rightEnabled"
};

#define CONFIG_PARAM_MENU 0
#define CONFIG_PARAM_APP_MENU 1
#define CONFIG_PARAM_TRIGGER 2
#define CONFIG_PARAM_GRIP 3
#define CONFIG_PARAM_TOUCHPAD 4
#define CONFIG_PARAM_TOUCHPAD_TOUCH 5
#define CONFIG_PARAM_TOUCHPAD_PRESS 6
#define CONFIG_PARAM_TOUCHPAD_AXES 7
#define CONFIG_PARAM_GRIP_OFFSETX 8
#define CONFIG_PARAM_GRIP_OFFSETY 9
#define CONFIG_PARAM_GRIP_OFFSETZ 10
#define CONFIG_PARAM_CONTROLLER_LEFTENABLED 11
#define CONFIG_PARAM_CONTROLLER_RIGHTENABLED 12

void CConfigHelper::LoadConfig()
{
    std::string l_path(g_ModuleFileName);
    l_path.erase(l_path.begin() + l_path.rfind('\\'), l_path.end());
    l_path.append("\\control_config.xml");

    pugi::xml_document *l_config = new pugi::xml_document();
    if(l_config->load_file(l_path.c_str()))
    {
        pugi::xml_node l_configRoot = l_config->child("config");
        if(l_configRoot)
        {
            for(pugi::xml_node l_node = l_configRoot.child("param"); l_node; l_node = l_node.next_sibling("param"))
            {
                pugi::xml_attribute l_attribName = l_node.attribute("name");
                if(l_attribName)
                {
                    std::string l_param(l_attribName.as_string());
                    pugi::xml_attribute l_attribValue = l_node.attribute("value");
                    if(l_attribValue)
                    {
                        switch(ReadEnumVector(l_param, g_configAttributeTable))
                        {
                            case CONFIG_PARAM_MENU:
                                ms_menu = l_attribValue.as_bool(true);
                                break;
                            case CONFIG_PARAM_APP_MENU:
                                ms_applicationMenu = l_attribValue.as_bool(true);
                                break;
                            case CONFIG_PARAM_TRIGGER:
                                ms_trigger = l_attribValue.as_bool(true);
                                break;
                            case CONFIG_PARAM_GRIP:
                                ms_grip = l_attribValue.as_bool(true);
                                break;
                            case CONFIG_PARAM_TOUCHPAD:
                                ms_touchpad = l_attribValue.as_bool(true);
                                break;
                            case CONFIG_PARAM_TOUCHPAD_TOUCH:
                                ms_touchpadTouch = l_attribValue.as_bool(true);
                                break;
                            case CONFIG_PARAM_TOUCHPAD_PRESS:
                                ms_touchpadPress = l_attribValue.as_bool(true);
                                break;
                            case CONFIG_PARAM_TOUCHPAD_AXES:
                                ms_touchpadAxes = l_attribValue.as_bool(true);
                                break;
                            case CONFIG_PARAM_GRIP_OFFSETX:
                                ms_gripOffsetX = l_attribValue.as_float(0.f);
                                break;
                            case CONFIG_PARAM_GRIP_OFFSETY:
                                ms_gripOffsetY = l_attribValue.as_float(0.f);
                                break;
                            case CONFIG_PARAM_GRIP_OFFSETZ:
                                ms_gripOffsetZ = l_attribValue.as_float(0.f);
                                break;
                            case CONFIG_PARAM_CONTROLLER_LEFTENABLED:
                                ms_controllerLeftEnabled = l_attribValue.as_bool(true);
                                break;
                            case CONFIG_PARAM_CONTROLLER_RIGHTENABLED:
                                ms_controllerRightEnabled = l_attribValue.as_bool(true);
                                break;
                        }
                    }
                }
            }
        }
    }

    delete l_config;
}