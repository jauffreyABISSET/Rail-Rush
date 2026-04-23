#pragma once

#include <GCE/Render/Structs.h>
#include "Transform.h"
#include <Aliases.h>

namespace sr
{
    class Light
    {
    public:
        Light() = default;
        virtual ~Light() {};
        
        void SetColor(gce::Vector4 color);

        static Light CreatePointLight(gce::Vector3f32 const& position, gce::Vector4 const& color, float32 range, float32 intensity, float32 strength);
        static Light CreateSpotLight(gce::Vector3f32 const& position, gce::Vector3f32 const& direction, gce::Vector4 const& color, float32 spotAngle, float32 penumbraAngle, float32 range, float32 intensity, float32 strength);
        static Light CreateDirectionalLight(gce::Vector3f32 const& direction, gce::Vector4 const& color, float32 intensity, float32 strength);
        void SetPosition(const gce::Vector3f32& pos);
        void UpdateGPU();

        static void AddLight(Light& light);
        static void RemoveLight(Light& light);
        
    private:
        Light(gce::LightData lightData) { m_Light = lightData; };
        gce::LightData m_Light;

    protected:
        Transform m_transform;
        bool m_isDirty = false;
    };
}
