/*
 * Copyright (c) 2024, An-Chi Liu <phy.tiger@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the copyright holder nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <modmesh/buffer/pymod/buffer_pymod.hpp> // Must be the first include.

namespace modmesh
{

namespace python
{

class MODMESH_PYTHON_WRAPPER_VISIBILITY WrapSimpleArrayPlex : public WrapBase<WrapSimpleArrayPlex, SimpleArrayPlex>
{
    using root_base_type = WrapBase<WrapSimpleArrayPlex, SimpleArrayPlex>;
    using wrapped_type = typename root_base_type::wrapped_type;
    using wrapper_type = typename root_base_type::wrapper_type;
    using shape_type = modmesh::detail::shape_type;

    friend root_base_type;

    WrapSimpleArrayPlex(pybind11::module & mod, char const * pyname, char const * pydoc)
        : root_base_type(mod, pyname, pydoc, pybind11::buffer_protocol())
    {
        (*this)
            .def_timed(
                pybind11::init(
                    [](pybind11::object const & shape, std::string const & datatype)
                    { return wrapped_type(make_shape(shape), datatype); }),
                pybind11::arg("shape"),
                pybind11::arg("dtype"))
            .def_timed(
                pybind11::init(&init_array_plex_with_value),
                pybind11::arg("shape"),
                pybind11::arg("value"),
                pybind11::arg("dtype"))
            .def(
                pybind11::init(
                    [](pybind11::array & arr_in)
                    {
                        shape_type shape;
                        for (ssize_t i = 0; i < arr_in.ndim(); ++i)
                        {
                            shape.push_back(arr_in.shape(i));
                        }
                        std::shared_ptr<ConcreteBuffer> const buffer = ConcreteBuffer::construct(
                            arr_in.nbytes(),
                            arr_in.mutable_data(),
                            std::make_unique<ConcreteBufferNdarrayRemover>(arr_in));
                        return wrapped_type(shape, buffer, pybind11::str(arr_in.dtype()));
                    }),
                pybind11::arg("array"))
            .def_property_readonly("typed", &get_typed_array)
            /// TODO: should have the same interface as WrapSimpleArray
            ;
    }

    /// Initialize the arrayplex with the given value
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    static wrapped_type init_array_plex_with_value(pybind11::object const & shape_in, pybind11::object const & value, std::string const & datatype)
    {
        const shape_type shape = make_shape(shape_in);
        wrapped_type array_plex(shape, datatype);

        // cast value to correct type based on the datatype
        switch (array_plex.data_type())
        {
        case DataType::Bool:
        {
            if (!pybind11::isinstance<pybind11::bool_>(value))
            {
                throw std::runtime_error("Data type mismatch, expected Python bool");
            }
            auto * array = static_cast<SimpleArrayBool *>(array_plex.mutable_instance_ptr());
            array->fill(value.cast<bool>());
            break;
        }
        case DataType::Int8:
        {
            if (!pybind11::isinstance<pybind11::int_>(value))
            {
                throw std::runtime_error("Data type mismatch, expected Python int");
            }
            auto * array = static_cast<SimpleArrayInt8 *>(array_plex.mutable_instance_ptr());
            array->fill(value.cast<int8_t>());
            break;
        }
        case DataType::Int16:
        {
            if (!pybind11::isinstance<pybind11::int_>(value))
            {
                throw std::runtime_error("Data type mismatch, expected Python int");
            }
            auto * array = static_cast<SimpleArrayInt16 *>(array_plex.mutable_instance_ptr());
            array->fill(value.cast<int16_t>());
            break;
        }
        case DataType::Int32:
        {
            if (!pybind11::isinstance<pybind11::int_>(value))
            {
                throw std::runtime_error("Data type mismatch, expected Python int");
            }
            auto * array = static_cast<SimpleArrayInt32 *>(array_plex.mutable_instance_ptr());
            array->fill(value.cast<int32_t>());
            break;
        }
        case DataType::Int64:
        {
            if (!pybind11::isinstance<pybind11::int_>(value))
            {
                throw std::runtime_error("Data type mismatch, expected Python int");
            }
            auto * array = static_cast<SimpleArrayInt64 *>(array_plex.mutable_instance_ptr());
            array->fill(value.cast<int64_t>());
            break;
        }
        case DataType::Uint8:
        {
            if (!pybind11::isinstance<pybind11::int_>(value))
            {
                throw std::runtime_error("Data type mismatch, expected Python int");
            }
            auto * array = static_cast<SimpleArrayUint8 *>(array_plex.mutable_instance_ptr());
            array->fill(value.cast<uint8_t>());
            break;
        }
        case DataType::Uint16:
        {
            if (!pybind11::isinstance<pybind11::int_>(value))
            {
                throw std::runtime_error("Data type mismatch, expected Python int");
            }
            auto * array = static_cast<SimpleArrayUint16 *>(array_plex.mutable_instance_ptr());
            array->fill(value.cast<uint16_t>());
            break;
        }
        case DataType::Uint32:
        {
            if (!pybind11::isinstance<pybind11::int_>(value))
            {
                throw std::runtime_error("Data type mismatch, expected Python int");
            }
            auto * array = static_cast<SimpleArrayUint32 *>(array_plex.mutable_instance_ptr());
            array->fill(value.cast<int32_t>());
            break;
        }
        case DataType::Uint64:
        {
            if (!pybind11::isinstance<pybind11::int_>(value))
            {
                throw std::runtime_error("Data type mismatch, expected Python int");
            }
            auto * array = static_cast<SimpleArrayUint64 *>(array_plex.mutable_instance_ptr());
            array->fill(value.cast<int64_t>());
            break;
        }
        case DataType::Float32:
        {
            if (!pybind11::isinstance<pybind11::float_>(value))
            {
                throw std::runtime_error("Data type mismatch, expected Python float");
            }
            auto * array = static_cast<SimpleArrayFloat32 *>(array_plex.mutable_instance_ptr());
            array->fill(value.cast<float>());
            break;
        }
        case DataType::Float64:
        {
            if (!pybind11::isinstance<pybind11::float_>(value))
            {
                throw std::runtime_error("Data type mismatch, expected Python float");
            }
            auto * array = static_cast<SimpleArrayFloat64 *>(array_plex.mutable_instance_ptr());
            array->fill(value.cast<double>());
            break;
        }
        default:
            throw std::runtime_error("Unsupported datatype");
        }
        return array_plex;
    }

    /// Return the typed function from the arrayplex
    static pybind11::object
    get_typed_array(wrapped_type const & array_plex)
    {
        switch (array_plex.data_type())
        {
        case DataType::Bool:
        {
            const auto * array = static_cast<const SimpleArrayBool *>(array_plex.instance_ptr());
            return pybind11::cast(std::move(SimpleArrayBool(*array)));
        }
        case DataType::Int8:
        {
            const auto * array = static_cast<const SimpleArrayInt8 *>(array_plex.instance_ptr());
            return pybind11::cast(std::move(SimpleArrayInt8(*array)));
        }
        case DataType::Int16:
        {
            const auto * array = static_cast<const SimpleArrayInt16 *>(array_plex.instance_ptr());
            return pybind11::cast(std::move(SimpleArrayInt16(*array)));
        }
        case DataType::Int32:
        {
            const auto * array = static_cast<const SimpleArrayInt32 *>(array_plex.instance_ptr());
            return pybind11::cast(std::move(SimpleArrayInt32(*array)));
        }
        case DataType::Int64:
        {
            const auto * array = static_cast<const SimpleArrayInt64 *>(array_plex.instance_ptr());
            return pybind11::cast(std::move(SimpleArrayInt64(*array)));
        }
        case DataType::Uint8:
        {
            const auto * array = static_cast<const SimpleArrayUint8 *>(array_plex.instance_ptr());
            return pybind11::cast(std::move(SimpleArrayUint8(*array)));
        }
        case DataType::Uint16:
        {
            const auto * array = static_cast<const SimpleArrayUint16 *>(array_plex.instance_ptr());
            return pybind11::cast(std::move(SimpleArrayUint16(*array)));
        }
        case DataType::Uint32:
        {
            const auto * array = static_cast<const SimpleArrayUint32 *>(array_plex.instance_ptr());
            return pybind11::cast(std::move(SimpleArrayUint32(*array)));
        }
        case DataType::Uint64:
        {
            const auto * array = static_cast<const SimpleArrayUint64 *>(array_plex.instance_ptr());
            return pybind11::cast(std::move(SimpleArrayUint64(*array)));
        }
        case DataType::Float32:
        {
            const auto * array = static_cast<const SimpleArrayFloat32 *>(array_plex.instance_ptr());
            return pybind11::cast(std::move(SimpleArrayFloat32(*array)));
        }
        case DataType::Float64:
        {
            const auto * array = static_cast<const SimpleArrayFloat64 *>(array_plex.instance_ptr());
            return pybind11::cast(std::move(SimpleArrayFloat64(*array)));
        }
        default:
        {
            throw std::runtime_error("Unsupported datatype");
        }
        }
    }

    static shape_type make_shape(pybind11::object const & shape_in)
    {
        shape_type shape;
        try
        {
            shape.push_back(shape_in.cast<size_t>());
        }
        catch (const pybind11::cast_error &)
        {
            shape = shape_in.cast<std::vector<size_t>>();
        }
        return shape;
    }
}; /* end of class WrapSimpleArrayPlex*/

void wrap_SimpleArrayPlex(pybind11::module & mod)
{
    WrapSimpleArrayPlex::commit(mod, "SimpleArray", "SimpleArray");
}

} /* end namespace python */

} /* end namespace modmesh */

// vim: set ff=unix fenc=utf8 et sw=4 ts=4 sts=4:
