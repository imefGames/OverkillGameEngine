#pragma once

namespace OK
{
    template <typename TestedClass>
    using IsPointer = std::is_pointer<TestedClass>;

    template <typename BaseClass, typename DerivedClass>
    using IsBaseOf = std::is_base_of<BaseClass, DerivedClass>;
}