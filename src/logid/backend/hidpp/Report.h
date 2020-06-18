#ifndef LOGID_BACKEND_HIDPP_REPORT_H
#define LOGID_BACKEND_HIDPP_REPORT_H

#include <cstdint>
#include "../raw/RawDevice.h"
#include "defs.h"

/* Some devices only support a subset of these reports */
#define HIDPP_REPORT_SHORT_SUPPORTED      1U
#define HIDPP_REPORT_LONG_SUPPORTED	      1U<<1U
/* Very long reports exist, however they have not been encountered so far */

namespace logid::backend::hidpp
{
    uint8_t getSupportedReports(std::vector<uint8_t>&& rdesc);

    namespace Offset
    {
        static constexpr uint8_t Type = 0;
        static constexpr uint8_t DeviceIndex = 1;
        static constexpr uint8_t Feature = 2;
        static constexpr uint8_t Function = 3;
        static constexpr uint8_t Parameters = 4;
    }

    class Report
    {
    public:
        typedef ReportType::ReportType Type;

        class InvalidReportID: public std::exception
        {
        public:
            InvalidReportID() = default;
            virtual const char* what() const noexcept;
        };

        class InvalidReportLength: public std::exception
        {
        public:
            InvalidReportLength() = default;;
            virtual const char* what() const noexcept;
        };

        static constexpr std::size_t MaxDataLength = 20;
        static constexpr uint8_t swIdMask = 0x0f;
        static constexpr uint8_t functionMask = 0x0f;

        Report(Report::Type type, DeviceIndex device_index,
                uint8_t feature_index,
                uint8_t function,
                uint8_t sw_id);
        explicit Report(const std::vector<uint8_t>& data);

        Report::Type type() const { return static_cast<Report::Type>(_data[Offset::Type]); };
        void setType(Report::Type type);

        std::vector<uint8_t>::iterator paramBegin() { return _data.begin() + Offset::Parameters; }
        std::vector<uint8_t>::iterator paramEnd() { return _data.end(); }
        void setParams(const std::vector<uint8_t>& _params);

        struct hidpp20_error
        {
            uint8_t feature_index, function, software_id, error_code;
        };

        bool isError20(hidpp20_error* error);

        logid::backend::hidpp::DeviceIndex deviceIndex()
        {
            return static_cast<DeviceIndex>(_data[Offset::DeviceIndex]);
        }

        std::vector<uint8_t> rawReport () const { return _data; }
    private:
        static constexpr std::size_t HeaderLength = 4;
        std::vector<uint8_t> _data;
    };
}

#endif //LOGID_BACKEND_HIDPP_REPORT_H