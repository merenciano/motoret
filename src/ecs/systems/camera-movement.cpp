#include "camera-movement.h"
#include "core/common-defs.h"
#include "core/manager.h"
#include "ecs/components/transform.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace leep
{
    CameraMovement::CameraMovement()
    {
        sensibility_ = 1.0f / 1000.0f;
        speed_ = 1.0f / 10.0f;
    }

    CameraMovement::CameraMovement(float sensibility, float speed)
    {
        sensibility_ = sensibility / 1000.0f;
        speed_ = speed / 10.0f;
    }

    void CameraMovement::executeSystem() const
    {
        static float mouse_down_pos[2] = { 0.0, 0.0 };
        static float fov = 70.0f;
        Transform tr;
        tr.transform_ = glm::inverse(GM.camera().view());

        // Rotation
        if (GM.input().isButtonDown(Button::MOUSE_RIGHT))
        {
            mouse_down_pos[0] = GM.input().mouseX();
            mouse_down_pos[1] = GM.input().mouseY();
        }

        if (GM.input().isButtonPressed(Button::MOUSE_RIGHT))
        {
            float mouse_offset[2] =
            { GM.input().mouseX() - mouse_down_pos[0], mouse_down_pos[1] - GM.input().mouseY() }; // Y axis inverted

            mouse_offset[0] *= sensibility_; // Sensibility
            mouse_offset[1] *= sensibility_;

            tr.rotateYWorld(-mouse_offset[0]);
            tr.transform_ = glm::rotate(tr.transform_, mouse_offset[1], glm::vec3(1.0f, 0.0f, 0.0f));

            mouse_down_pos[0] = GM.input().mouseX();
            mouse_down_pos[1] = GM.input().mouseY();
        }

        // Position
        if (GM.input().isButtonPressed(Button::UP))
        {
            tr.transform_ = glm::translate(tr.transform_, glm::vec3(0.0f, 0.0f, -speed_));
        }

        if (GM.input().isButtonPressed(Button::DOWN))
        {
            tr.transform_ = glm::translate(tr.transform_, glm::vec3(0.0f, 0.0f, speed_));
        }

        if (GM.input().isButtonPressed(Button::LEFT))
        {
            tr.transform_ = glm::translate(tr.transform_, glm::vec3(-speed_, 0.0f, 0.0f));
        }

        if (GM.input().isButtonPressed(Button::RIGHT))
        {
            tr.transform_ = glm::translate(tr.transform_, glm::vec3(speed_, 0.0f, 0.0f));
        }

        if (GM.input().isButtonPressed(Button::B1))
        {
            tr.transform_ = glm::translate(tr.transform_, glm::vec3(0.0f, speed_, 0.0f));
        }

        if (GM.input().isButtonPressed(Button::B4))
        {
            tr.transform_ = glm::translate(tr.transform_, glm::vec3(0.0f, -speed_, 0.0f));
        }

        if (GM.input().scroll() != 0.0f)
        {
            fov -= GM.input().scroll() * 5.0f;
            fov = glm::clamp(fov, 1.0f, 70.0f);
            GM.camera().set_projection(glm::radians(fov), (float)GM.window().width() / GM.window().height(), 0.1f, 80.0f);
        }

        GM.camera().set_view(glm::inverse(tr.transform_));
    }
}