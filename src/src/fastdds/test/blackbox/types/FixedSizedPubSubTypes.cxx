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
 * @file FixedSizedPubSubTypes.cpp
 * This header file contains the implementation of the serialization functions.
 *
 * This file was generated by the tool fastddsgen.
 */

#include "FixedSizedPubSubTypes.hpp"

#include <fastdds/dds/log/Log.hpp>
#include <fastdds/rtps/common/CdrSerialization.hpp>

#include "FixedSizedCdrAux.hpp"
#include "FixedSizedTypeObjectSupport.hpp"

using SerializedPayload_t = eprosima::fastdds::rtps::SerializedPayload_t;
using InstanceHandle_t = eprosima::fastdds::rtps::InstanceHandle_t;
using DataRepresentationId_t = eprosima::fastdds::dds::DataRepresentationId_t;

FixedSizedPubSubType::FixedSizedPubSubType()
{
    set_name("FixedSized");
    uint32_t type_size = FixedSized_max_cdr_typesize;
    type_size += static_cast<uint32_t>(eprosima::fastcdr::Cdr::alignment(type_size, 4)); /* possible submessage alignment */
    max_serialized_type_size = type_size + 4; /*encapsulation*/
    is_compute_key_provided = false;
    uint32_t key_length = FixedSized_max_key_cdr_typesize > 16 ? FixedSized_max_key_cdr_typesize : 16;
    key_buffer_ = reinterpret_cast<unsigned char*>(malloc(key_length));
    memset(key_buffer_, 0, key_length);
}

FixedSizedPubSubType::~FixedSizedPubSubType()
{
    if (key_buffer_ != nullptr)
    {
        free(key_buffer_);
    }
}

bool FixedSizedPubSubType::serialize(
        const void* const data,
        SerializedPayload_t& payload,
        DataRepresentationId_t data_representation)
{
    const FixedSized* p_type = static_cast<const FixedSized*>(data);

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
        eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR2);

    try
    {
        // Serialize encapsulation
        ser.serialize_encapsulation();
        // Serialize the object.
        ser << *p_type;
        ser.set_dds_cdr_options({0,0});
    }
    catch (eprosima::fastcdr::exception::Exception& /*exception*/)
    {
        return false;
    }

    // Get the serialized length
    payload.length = static_cast<uint32_t>(ser.get_serialized_data_length());
    return true;
}

bool FixedSizedPubSubType::deserialize(
        SerializedPayload_t& payload,
        void* data)
{
    try
    {
        // Convert DATA to pointer of your type
        FixedSized* p_type = static_cast<FixedSized*>(data);

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

uint32_t FixedSizedPubSubType::calculate_serialized_size(
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
                    *static_cast<const FixedSized*>(data), current_alignment)) +
                4u /*encapsulation*/;
    }
    catch (eprosima::fastcdr::exception::Exception& /*exception*/)
    {
        return 0;
    }
}

void* FixedSizedPubSubType::create_data()
{
    return reinterpret_cast<void*>(new FixedSized());
}

void FixedSizedPubSubType::delete_data(
        void* data)
{
    delete(reinterpret_cast<FixedSized*>(data));
}

bool FixedSizedPubSubType::compute_key(
        SerializedPayload_t& payload,
        InstanceHandle_t& handle,
        bool force_md5)
{
    if (!is_compute_key_provided)
    {
        return false;
    }

    FixedSized data;
    if (deserialize(payload, static_cast<void*>(&data)))
    {
        return compute_key(static_cast<void*>(&data), handle, force_md5);
    }

    return false;
}

bool FixedSizedPubSubType::compute_key(
        const void* const data,
        InstanceHandle_t& handle,
        bool force_md5)
{
    if (!is_compute_key_provided)
    {
        return false;
    }

    const FixedSized* p_type = static_cast<const FixedSized*>(data);

    // Object that manages the raw buffer.
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(key_buffer_),
            FixedSized_max_key_cdr_typesize);

    // Object that serializes the data.
    eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS, eprosima::fastcdr::CdrVersion::XCDRv2);
    ser.set_encoding_flag(eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR2);
    eprosima::fastcdr::serialize_key(ser, *p_type);
    if (force_md5 || FixedSized_max_key_cdr_typesize > 16)
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

void FixedSizedPubSubType::register_type_object_representation()
{
    register_FixedSized_type_identifier(type_identifiers_);
}


// Include auxiliary functions like for serializing/deserializing.
#include "FixedSizedCdrAux.ipp"
