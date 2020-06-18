#ifndef LOGID_BACKEND_HIDPP20_FEATURE_ROOT_H
#define LOGID_BACKEND_HIDPP20_FEATURE_ROOT_H

#include "../Feature.h"
#include "../feature_defs.h"

namespace logid {
namespace backend {
namespace hidpp20
{
    class Root : public Feature
    {
    public:
        static const uint16_t ID = FeatureID::ROOT;
        virtual uint16_t getID() { return ID; }

        enum Function : uint8_t
        {
            GetFeature = 0,
            Ping = 1
        };

        Root(Device* device);

        feature_info getFeature (uint16_t feature_id);
        void ping();
    private:
        enum FeatureFlag : uint8_t
        {
            Obsolete = 1<<7,
            Hidden = 1<<6,
            Internal = 1<<5
        };
    };
}}}

#endif //LOGID_BACKEND_HIDPP20_FEATURE_ROOT_H