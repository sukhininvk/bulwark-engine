#include "Bulwark/input.h"

#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_log.h>

namespace
{
    const char* PressState(const bool down)
    {
        return down ? "pressed" : "released";
    }

    const char* MouseButtonName(const Uint8 button)
    {
        switch (button)
        {
        case SDL_BUTTON_LEFT:
            return "left";
        case SDL_BUTTON_MIDDLE:
            return "middle";
        case SDL_BUTTON_RIGHT:
            return "right";
        case SDL_BUTTON_X1:
            return "x1";
        case SDL_BUTTON_X2:
            return "x2";
        default:
            return "unknown";
        }
    }

    const char* HatDirectionName(const Uint8 value)
    {
        switch (value)
        {
        case SDL_HAT_CENTERED:
            return "centered";
        case SDL_HAT_UP:
            return "up";
        case SDL_HAT_RIGHT:
            return "right";
        case SDL_HAT_DOWN:
            return "down";
        case SDL_HAT_LEFT:
            return "left";
        case SDL_HAT_RIGHTUP:
            return "right-up";
        case SDL_HAT_RIGHTDOWN:
            return "right-down";
        case SDL_HAT_LEFTUP:
            return "left-up";
        case SDL_HAT_LEFTDOWN:
            return "left-down";
        default:
            return "unknown";
        }
    }

    const char* GamepadAxisName(const Uint8 axis)
    {
        const char* name = SDL_GetGamepadStringForAxis(static_cast<SDL_GamepadAxis>(axis));
        return name ? name : "unknown";
    }

    const char* GamepadButtonName(const Uint8 button)
    {
        const char* name = SDL_GetGamepadStringForButton(static_cast<SDL_GamepadButton>(button));
        return name ? name : "unknown";
    }
}

namespace Bulwark
{
    void Input::HandleEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
        case SDL_EVENT_KEYBOARD_ADDED:
            SDL_Log("Keyboard added: id=%u", event.kdevice.which);
            break;
        case SDL_EVENT_KEYBOARD_REMOVED:
            SDL_Log("Keyboard removed: id=%u", event.kdevice.which);
            break;
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP:
            SDL_Log(
                "Keyboard %s: key=%s scancode=%s id=%u repeat=%s",
                PressState(event.key.down),
                SDL_GetKeyName(event.key.key),
                SDL_GetScancodeName(event.key.scancode),
                event.key.which,
                event.key.repeat ? "true" : "false"
            );
            break;
        case SDL_EVENT_TEXT_INPUT:
            SDL_Log("Text input: \"%s\"", event.text.text);
            break;
        case SDL_EVENT_MOUSE_ADDED:
            SDL_Log("Mouse added: id=%u", event.mdevice.which);
            break;
        case SDL_EVENT_MOUSE_REMOVED:
            SDL_Log("Mouse removed: id=%u", event.mdevice.which);
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            SDL_Log(
                "Mouse button %s: button=%s(%u) id=%u clicks=%u position=(%.1f, %.1f)",
                PressState(event.button.down),
                MouseButtonName(event.button.button),
                event.button.button,
                event.button.which,
                event.button.clicks,
                event.button.x,
                event.button.y
            );
            break;
        case SDL_EVENT_MOUSE_MOTION:
            SDL_Log(
                "Mouse motion: id=%u position=(%.1f, %.1f) delta=(%.1f, %.1f)",
                event.motion.which,
                event.motion.x,
                event.motion.y,
                event.motion.xrel,
                event.motion.yrel
            );
            break;
        case SDL_EVENT_MOUSE_WHEEL:
            SDL_Log(
                "Mouse wheel: id=%u scroll=(%.2f, %.2f) mouse=(%.1f, %.1f)",
                event.wheel.which,
                event.wheel.x,
                event.wheel.y,
                event.wheel.mouse_x,
                event.wheel.mouse_y
            );
            break;
        case SDL_EVENT_JOYSTICK_ADDED:
            SDL_Log("Joystick added: id=%u", event.jdevice.which);
            break;
        case SDL_EVENT_JOYSTICK_REMOVED:
            SDL_Log("Joystick removed: id=%u", event.jdevice.which);
            break;
        case SDL_EVENT_JOYSTICK_AXIS_MOTION:
            SDL_Log(
                "Joystick axis: id=%u axis=%u value=%d",
                event.jaxis.which,
                event.jaxis.axis,
                event.jaxis.value
            );
            break;
        case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
        case SDL_EVENT_JOYSTICK_BUTTON_UP:
            SDL_Log(
                "Joystick button %s: id=%u button=%u",
                PressState(event.jbutton.down),
                event.jbutton.which,
                event.jbutton.button
            );
            break;
        case SDL_EVENT_JOYSTICK_HAT_MOTION:
            SDL_Log(
                "Joystick hat: id=%u hat=%u direction=%s(%u)",
                event.jhat.which,
                event.jhat.hat,
                HatDirectionName(event.jhat.value),
                event.jhat.value
            );
            break;
        case SDL_EVENT_JOYSTICK_BALL_MOTION:
            SDL_Log(
                "Joystick ball: id=%u ball=%u delta=(%d, %d)",
                event.jball.which,
                event.jball.ball,
                event.jball.xrel,
                event.jball.yrel
            );
            break;
        case SDL_EVENT_GAMEPAD_ADDED:
            SDL_Log("Gamepad added: id=%u name=%s", event.gdevice.which, SDL_GetGamepadNameForID(event.gdevice.which));
            break;
        case SDL_EVENT_GAMEPAD_REMOVED:
            SDL_Log("Gamepad removed: id=%u", event.gdevice.which);
            break;
        case SDL_EVENT_GAMEPAD_REMAPPED:
            SDL_Log("Gamepad remapped: id=%u", event.gdevice.which);
            break;
        case SDL_EVENT_GAMEPAD_AXIS_MOTION:
            SDL_Log(
                "Gamepad axis: id=%u axis=%s(%u) value=%d",
                event.gaxis.which,
                GamepadAxisName(event.gaxis.axis),
                event.gaxis.axis,
                event.gaxis.value
            );
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
        case SDL_EVENT_GAMEPAD_BUTTON_UP:
            SDL_Log(
                "Gamepad button %s: id=%u button=%s(%u)",
                PressState(event.gbutton.down),
                event.gbutton.which,
                GamepadButtonName(event.gbutton.button),
                event.gbutton.button
            );
            break;
        case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
        case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
        case SDL_EVENT_GAMEPAD_TOUCHPAD_UP:
            SDL_Log(
                "Gamepad touchpad: id=%u touchpad=%d finger=%d position=(%.2f, %.2f) pressure=%.2f",
                event.gtouchpad.which,
                event.gtouchpad.touchpad,
                event.gtouchpad.finger,
                event.gtouchpad.x,
                event.gtouchpad.y,
                event.gtouchpad.pressure
            );
            break;
        case SDL_EVENT_GAMEPAD_SENSOR_UPDATE:
            SDL_Log(
                "Gamepad sensor: id=%u sensor=%d data=(%.3f, %.3f, %.3f)",
                event.gsensor.which,
                event.gsensor.sensor,
                event.gsensor.data[0],
                event.gsensor.data[1],
                event.gsensor.data[2]
            );
            break;
        case SDL_EVENT_FINGER_DOWN:
        case SDL_EVENT_FINGER_UP:
        case SDL_EVENT_FINGER_MOTION:
        case SDL_EVENT_FINGER_CANCELED:
            SDL_Log(
                "Touch: touch=%llu finger=%llu position=(%.2f, %.2f) delta=(%.2f, %.2f) pressure=%.2f",
                event.tfinger.touchID,
                event.tfinger.fingerID,
                event.tfinger.x,
                event.tfinger.y,
                event.tfinger.dx,
                event.tfinger.dy,
                event.tfinger.pressure
            );
            break;
        case SDL_EVENT_PEN_PROXIMITY_IN:
        case SDL_EVENT_PEN_PROXIMITY_OUT:
            SDL_Log("Pen proximity: id=%u in_range=%s", event.pproximity.which, event.type == SDL_EVENT_PEN_PROXIMITY_IN ? "true" : "false");
            break;
        case SDL_EVENT_PEN_DOWN:
        case SDL_EVENT_PEN_UP:
            SDL_Log(
                "Pen touch %s: id=%u position=(%.1f, %.1f) eraser=%s",
                PressState(event.ptouch.down),
                event.ptouch.which,
                event.ptouch.x,
                event.ptouch.y,
                event.ptouch.eraser ? "true" : "false"
            );
            break;
        case SDL_EVENT_PEN_BUTTON_DOWN:
        case SDL_EVENT_PEN_BUTTON_UP:
            SDL_Log(
                "Pen button %s: id=%u button=%u position=(%.1f, %.1f)",
                PressState(event.pbutton.down),
                event.pbutton.which,
                event.pbutton.button,
                event.pbutton.x,
                event.pbutton.y
            );
            break;
        case SDL_EVENT_PEN_MOTION:
            SDL_Log("Pen motion: id=%u position=(%.1f, %.1f)", event.pmotion.which, event.pmotion.x, event.pmotion.y);
            break;
        case SDL_EVENT_PEN_AXIS:
            SDL_Log(
                "Pen axis: id=%u axis=%d value=%.3f position=(%.1f, %.1f)",
                event.paxis.which,
                event.paxis.axis,
                event.paxis.value,
                event.paxis.x,
                event.paxis.y
            );
            break;
        default:
            break;
        }
    }
}
