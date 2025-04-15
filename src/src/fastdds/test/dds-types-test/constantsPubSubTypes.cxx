// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file constantsPubSubTypes.cpp
 * This header file contains the implementation of the serialization functions.
 *
 * This file was generated by the tool fastddsgen.
 */

#include "constantsPubSubTypes.hpp"

#include <fastdds/dds/log/Log.hpp>
#include <fastdds/rtps/common/CdrSerialization.hpp>

#include "constantsCdrAux.hpp"
#include "constantsTypeObjectSupport.hpp"

using SerializedPayload_t = eprosima::fastdds::rtps::SerializedPayload_t;
using InstanceHandle_t = eprosima::fastdds::rtps::InstanceHandle_t;
using DataRepresentationId_t = eprosima::fastdds::dds::DataRepresentationId_t;

namespace const_module1 {
    ModuleConstsLiteralsStructPubSubType::ModuleConstsLiteralsStructPubSubType()
    {
        set_name("const_module1::ModuleConstsLiteralsStruct");
        uint32_t type_size = const_module1_ModuleConstsLiteralsStruct_max_cdr_typesize;
        type_size += static_cast<uint32_t>(eprosima::fastcdr::Cdr::alignment(type_size, 4)); /* possible submessage alignment */
        max_serialized_type_size = type_size + 4; /*encapsulation*/
        is_compute_key_provided = false;
        uint32_t key_length = const_module1_ModuleConstsLiteralsStruct_max_key_cdr_typesize > 16 ? const_module1_ModuleConstsLiteralsStruct_max_key_cdr_typesize : 16;
        key_buffer_ = reinterpret_cast<unsigned char*>(malloc(key_length));
        memset(key_buffer_, 0, key_length);
    }

    ModuleConstsLiteralsStructPubSubType::~ModuleConstsLiteralsStructPubSubType()
    {
        if (key_buffer_ != nullptr)
        {
            free(key_buffer_);
        }
    }

    bool ModuleConstsLiteralsStructPubSubType::serialize(
            const void* const data,
            SerializedPayload_t& payload,
            DataRepresentationId_t data_representation)
    {
        const ModuleConstsLiteralsStruct* p_type = static_cast<const ModuleConstsLiteralsStruct*>(data);

        // Object that manages the raw buffer.
        eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload.data), payload.max_size);
        // Object that serializes the data.
        eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
                data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
                eprosima::fastcdr::CdrVersion::XCDRv1 : eprosima::fastcdr::CdrVersion::XCDRv2);
        payload.encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
        ser.set_encoding_flag(
            data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
            eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR  :
            eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2);

        try
        {
            // Serialize encapsulation
            ser.serialize_encapsulation();
            // Serialize the object.
            ser << *p_type;
        }
        catch (eprosima::fastcdr::exception::Exception& /*exception*/)
        {
            return false;
        }

        // Get the serialized length
        payload.length = static_cast<uint32_t>(ser.get_serialized_data_length());
        return true;
    }

    bool ModuleConstsLiteralsStructPubSubType::deserialize(
            SerializedPayload_t& payload,
            void* data)
    {
        try
        {
            // Convert DATA to pointer of your type
            ModuleConstsLiteralsStruct* p_type = static_cast<ModuleConstsLiteralsStruct*>(data);

            // Object that manages the raw buffer.
            eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload.data), payload.length);

            // Object that deserializes the data.
            eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN);

            // Deserialize encapsulation.
            deser.read_encapsulation();
            payload.encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

            // Deserialize the object.
            deser >> *p_type;
        }
        catch (eprosima::fastcdr::exception::Exception& /*exception*/)
        {
            return false;
        }

        return true;
    }

    uint32_t ModuleConstsLiteralsStructPubSubType::calculate_serialized_size(
            const void* const data,
            DataRepresentationId_t data_representation)
    {
        try
        {
            eprosima::fastcdr::CdrSizeCalculator calculator(
                data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
                eprosima::fastcdr::CdrVersion::XCDRv1 :eprosima::fastcdr::CdrVersion::XCDRv2);
            size_t current_alignment {0};
            return static_cast<uint32_t>(calculator.calculate_serialized_size(
                        *static_cast<const ModuleConstsLiteralsStruct*>(data), current_alignment)) +
                    4u /*encapsulation*/;
        }
        catch (eprosima::fastcdr::exception::Exception& /*exception*/)
        {
            return 0;
        }
    }

    void* ModuleConstsLiteralsStructPubSubType::create_data()
    {
        return reinterpret_cast<void*>(new ModuleConstsLiteralsStruct());
    }

    void ModuleConstsLiteralsStructPubSubType::delete_data(
            void* data)
    {
        delete(reinterpret_cast<ModuleConstsLiteralsStruct*>(data));
    }

    bool ModuleConstsLiteralsStructPubSubType::compute_key(
            SerializedPayload_t& payload,
            InstanceHandle_t& handle,
            bool force_md5)
    {
        if (!is_compute_key_provided)
        {
            return false;
        }

        ModuleConstsLiteralsStruct data;
        if (deserialize(payload, static_cast<void*>(&data)))
        {
            return compute_key(static_cast<void*>(&data), handle, force_md5);
        }

        return false;
    }

    bool ModuleConstsLiteralsStructPubSubType::compute_key(
            const void* const data,
            InstanceHandle_t& handle,
            bool force_md5)
    {
        if (!is_compute_key_provided)
        {
            return false;
        }

        const ModuleConstsLiteralsStruct* p_type = static_cast<const ModuleConstsLiteralsStruct*>(data);

        // Object that manages the raw buffer.
        eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(key_buffer_),
                const_module1_ModuleConstsLiteralsStruct_max_key_cdr_typesize);

        // Object that serializes the data.
        eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS, eprosima::fastcdr::CdrVersion::XCDRv2);
        ser.set_encoding_flag(eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR2);
        eprosima::fastcdr::serialize_key(ser, *p_type);
        if (force_md5 || const_module1_ModuleConstsLiteralsStruct_max_key_cdr_typesize > 16)
        {
            md5_.init();
            md5_.update(key_buffer_, static_cast<unsigned int>(ser.get_serialized_data_length()));
            md5_.finalize();
            for (uint8_t i = 0; i < 16; ++i)
            {
                handle.value[i] = md5_.digest[i];
            }
        }
        else
        {
            for (uint8_t i = 0; i < 16; ++i)
            {
                handle.value[i] = key_buffer_[i];
            }
        }
        return true;
    }

    void ModuleConstsLiteralsStructPubSubType::register_type_object_representation()
    {
        register_ModuleConstsLiteralsStruct_type_identifier(type_identifiers_);
    }

} // namespace const_module1

namespace const_module2 {
    Module2ConstsLiteralsStructPubSubType::Module2ConstsLiteralsStructPubSubType()
    {
        set_name("const_module2::Module2ConstsLiteralsStruct");
        uint32_t type_size = const_module2_Module2ConstsLiteralsStruct_max_cdr_typesize;
        type_size += static_cast<uint32_t>(eprosima::fastcdr::Cdr::alignment(type_size, 4)); /* possible submessage alignment */
        max_serialized_type_size = type_size + 4; /*encapsulation*/
        is_compute_key_provided = false;
        uint32_t key_length = const_module2_Module2ConstsLiteralsStruct_max_key_cdr_typesize > 16 ? const_module2_Module2ConstsLiteralsStruct_max_key_cdr_typesize : 16;
        key_buffer_ = reinterpret_cast<unsigned char*>(malloc(key_length));
        memset(key_buffer_, 0, key_length);
    }

    Module2ConstsLiteralsStructPubSubType::~Module2ConstsLiteralsStructPubSubType()
    {
        if (key_buffer_ != nullptr)
        {
            free(key_buffer_);
        }
    }

    bool Module2ConstsLiteralsStructPubSubType::serialize(
            const void* const data,
            SerializedPayload_t& payload,
            DataRepresentationId_t data_representation)
    {
        const Module2ConstsLiteralsStruct* p_type = static_cast<const Module2ConstsLiteralsStruct*>(data);

        // Object that manages the raw buffer.
        eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload.data), payload.max_size);
        // Object that serializes the data.
        eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
                data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
                eprosima::fastcdr::CdrVersion::XCDRv1 : eprosima::fastcdr::CdrVersion::XCDRv2);
        payload.encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
        ser.set_encoding_flag(
            data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
            eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR  :
            eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2);

        try
        {
            // Serialize encapsulation
            ser.serialize_encapsulation();
            // Serialize the object.
            ser << *p_type;
        }
        catch (eprosima::fastcdr::exception::Exception& /*exception*/)
        {
            return false;
        }

        // Get the serialized length
        payload.length = static_cast<uint32_t>(ser.get_serialized_data_length());
        return true;
    }

    bool Module2ConstsLiteralsStructPubSubType::deserialize(
            SerializedPayload_t& payload,
            void* data)
    {
        try
        {
            // Convert DATA to pointer of your type
            Module2ConstsLiteralsStruct* p_type = static_cast<Module2ConstsLiteralsStruct*>(data);

            // Object that manages the raw buffer.
            eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload.data), payload.length);

            // Object that deserializes the data.
            eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN);

            // Deserialize encapsulation.
            deser.read_encapsulation();
            payload.encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

            // Deserialize the object.
            deser >> *p_type;
        }
        catch (eprosima::fastcdr::exception::Exception& /*exception*/)
        {
            return false;
        }

        return true;
    }

    uint32_t Module2ConstsLiteralsStructPubSubType::calculate_serialized_size(
            const void* const data,
            DataRepresentationId_t data_representation)
    {
        try
        {
            eprosima::fastcdr::CdrSizeCalculator calculator(
                data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
                eprosima::fastcdr::CdrVersion::XCDRv1 :eprosima::fastcdr::CdrVersion::XCDRv2);
            size_t current_alignment {0};
            return static_cast<uint32_t>(calculator.calculate_serialized_size(
                        *static_cast<const Module2ConstsLiteralsStruct*>(data), current_alignment)) +
                    4u /*encapsulation*/;
        }
        catch (eprosima::fastcdr::exception::Exception& /*exception*/)
        {
            return 0;
        }
    }

    void* Module2ConstsLiteralsStructPubSubType::create_data()
    {
        return reinterpret_cast<void*>(new Module2ConstsLiteralsStruct());
    }

    void Module2ConstsLiteralsStructPubSubType::delete_data(
            void* data)
    {
        delete(reinterpret_cast<Module2ConstsLiteralsStruct*>(data));
    }

    bool Module2ConstsLiteralsStructPubSubType::compute_key(
            SerializedPayload_t& payload,
            InstanceHandle_t& handle,
            bool force_md5)
    {
        if (!is_compute_key_provided)
        {
            return false;
        }

        Module2ConstsLiteralsStruct data;
        if (deserialize(payload, static_cast<void*>(&data)))
        {
            return compute_key(static_cast<void*>(&data), handle, force_md5);
        }

        return false;
    }

    bool Module2ConstsLiteralsStructPubSubType::compute_key(
            const void* const data,
            InstanceHandle_t& handle,
            bool force_md5)
    {
        if (!is_compute_key_provided)
        {
            return false;
        }

        const Module2ConstsLiteralsStruct* p_type = static_cast<const Module2ConstsLiteralsStruct*>(data);

        // Object that manages the raw buffer.
        eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(key_buffer_),
                const_module2_Module2ConstsLiteralsStruct_max_key_cdr_typesize);

        // Object that serializes the data.
        eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS, eprosima::fastcdr::CdrVersion::XCDRv2);
        ser.set_encoding_flag(eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR2);
        eprosima::fastcdr::serialize_key(ser, *p_type);
        if (force_md5 || const_module2_Module2ConstsLiteralsStruct_max_key_cdr_typesize > 16)
        {
            md5_.init();
            md5_.update(key_buffer_, static_cast<unsigned int>(ser.get_serialized_data_length()));
            md5_.finalize();
            for (uint8_t i = 0; i < 16; ++i)
            {
                handle.value[i] = md5_.digest[i];
            }
        }
        else
        {
            for (uint8_t i = 0; i < 16; ++i)
            {
                handle.value[i] = key_buffer_[i];
            }
        }
        return true;
    }

    void Module2ConstsLiteralsStructPubSubType::register_type_object_representation()
    {
        register_Module2ConstsLiteralsStruct_type_identifier(type_identifiers_);
    }

} // namespace const_module2

ConstsLiteralsStructPubSubType::ConstsLiteralsStructPubSubType()
{
    set_name("ConstsLiteralsStruct");
    uint32_t type_size = ConstsLiteralsStruct_max_cdr_typesize;
    type_size += static_cast<uint32_t>(eprosima::fastcdr::Cdr::alignment(type_size, 4)); /* possible submessage alignment */
    max_serialized_type_size = type_size + 4; /*encapsulation*/
    is_compute_key_provided = false;
    uint32_t key_length = ConstsLiteralsStruct_max_key_cdr_typesize > 16 ? ConstsLiteralsStruct_max_key_cdr_typesize : 16;
    key_buffer_ = reinterpret_cast<unsigned char*>(malloc(key_length));
    memset(key_buffer_, 0, key_length);
}

ConstsLiteralsStructPubSubType::~ConstsLiteralsStructPubSubType()
{
    if (key_buffer_ != nullptr)
    {
        free(key_buffer_);
    }
}

bool ConstsLiteralsStructPubSubType::serialize(
        const void* const data,
        SerializedPayload_t& payload,
        DataRepresentationId_t data_representation)
{
    const ConstsLiteralsStruct* p_type = static_cast<const ConstsLiteralsStruct*>(data);

    // Object that manages the raw buffer.
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload.data), payload.max_size);
    // Object that serializes the data.
    eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
            data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
            eprosima::fastcdr::CdrVersion::XCDRv1 : eprosima::fastcdr::CdrVersion::XCDRv2);
    payload.encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
    ser.set_encoding_flag(
        data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
        eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR  :
        eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2);

    try
    {
        // Serialize encapsulation
        ser.serialize_encapsulation();
        // Serialize the object.
        ser << *p_type;
    }
    catch (eprosima::fastcdr::exception::Exception& /*exception*/)
    {
        return false;
    }

    // Get the serialized length
    payload.length = static_cast<uint32_t>(ser.get_serialized_data_length());
    return true;
}

bool ConstsLiteralsStructPubSubType::deserialize(
        SerializedPayload_t& payload,
        void* data)
{
    try
    {
        // Convert DATA to pointer of your type
        ConstsLiteralsStruct* p_type = static_cast<ConstsLiteralsStruct*>(data);

        // Object that manages the raw buffer.
        eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload.data), payload.length);

        // Object that deserializes the data.
        eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN);

        // Deserialize encapsulation.
        deser.read_encapsulation();
        payload.encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

        // Deserialize the object.
        deser >> *p_type;
    }
    catch (eprosima::fastcdr::exception::Exception& /*exception*/)
    {
        return false;
    }

    return true;
}

uint32_t ConstsLiteralsStructPubSubType::calculate_serialized_size(
        const void* const data,
        DataRepresentationId_t data_representation)
{
    try
    {
        eprosima::fastcdr::CdrSizeCalculator calculator(
            data_representation == DataRepresentationId_t::XCDR_DATA_REPRESENTATION ?
            eprosima::fastcdr::CdrVersion::XCDRv1 :eprosima::fastcdr::CdrVersion::XCDRv2);
        size_t current_alignment {0};
        return static_cast<uint32_t>(calculator.calculate_serialized_size(
                    *static_cast<const ConstsLiteralsStruct*>(data), current_alignment)) +
                4u /*encapsulation*/;
    }
    catch (eprosima::fastcdr::exception::Exception& /*exception*/)
    {
        return 0;
    }
}

void* ConstsLiteralsStructPubSubType::create_data()
{
    return reinterpret_cast<void*>(new ConstsLiteralsStruct());
}

void ConstsLiteralsStructPubSubType::delete_data(
        void* data)
{
    delete(reinterpret_cast<ConstsLiteralsStruct*>(data));
}

bool ConstsLiteralsStructPubSubType::compute_key(
        SerializedPayload_t& payload,
        InstanceHandle_t& handle,
        bool force_md5)
{
    if (!is_compute_key_provided)
    {
        return false;
    }

    ConstsLiteralsStruct data;
    if (deserialize(payload, static_cast<void*>(&data)))
    {
        return compute_key(static_cast<void*>(&data), handle, force_md5);
    }

    return false;
}

bool ConstsLiteralsStructPubSubType::compute_key(
        const void* const data,
        InstanceHandle_t& handle,
        bool force_md5)
{
    if (!is_compute_key_provided)
    {
        return false;
    }

    const ConstsLiteralsStruct* p_type = static_cast<const ConstsLiteralsStruct*>(data);

    // Object that manages the raw buffer.
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(key_buffer_),
            ConstsLiteralsStruct_max_key_cdr_typesize);

    // Object that serializes the data.
    eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS, eprosima::fastcdr::CdrVersion::XCDRv2);
    ser.set_encoding_flag(eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR2);
    eprosima::fastcdr::serialize_key(ser, *p_type);
    if (force_md5 || ConstsLiteralsStruct_max_key_cdr_typesize > 16)
    {
        md5_.init();
        md5_.update(key_buffer_, static_cast<unsigned int>(ser.get_serialized_data_length()));
        md5_.finalize();
        for (uint8_t i = 0; i < 16; ++i)
        {
            handle.value[i] = md5_.digest[i];
        }
    }
    else
    {
        for (uint8_t i = 0; i < 16; ++i)
        {
            handle.value[i] = key_buffer_[i];
        }
    }
    return true;
}

void ConstsLiteralsStructPubSubType::register_type_object_representation()
{
    register_ConstsLiteralsStruct_type_identifier(type_identifiers_);
}


// Include auxiliary functions like for serializing/deserializing.
#include "constantsCdrAux.ipp"
