#pragma once

#include <common/types.h>
#include <core/kernel/kernel_obj.h>

#include <array>
#include <cstdint>
#include <memory>

namespace eka2l1 {
    using kernel_obj_ptr = std::shared_ptr<kernel::kernel_obj>;
    class kernel_system;

    namespace kernel {
        enum class special_handle_type : uint32_t {
            crr_process = 0xFFFF8000,
            crr_thread = 0xFFFF8001
        };

        struct handle_inspect_info {
            bool handle_array_local;
            int object_ix_index;
            int object_ix_next_instance;
            bool no_close;

            bool special;
            special_handle_type special_type;
        };

        handle_inspect_info inspect_handle(uint32_t handle);

        enum class handle_array_owner {
            thread,
            process,
            kernel
        };

        struct object_ix_record {
            kernel_obj_ptr object;
            uint32_t associated_handle;
            bool free = true;
        };

        /*! \brief The ultimate object handles holder. */
        class object_ix {
            uint64_t uid;

            size_t next_instance;
            std::array<object_ix_record, 0x100> objects;

            handle_array_owner owner;

            uint32_t make_handle(size_t index);

            kernel_system *kern;

        public:
            object_ix() {}
            object_ix(kernel_system *kern, handle_array_owner owner);

            /*! \brief Add new object to the ix. 
             * \returns Handle to the object
            */
            uint32_t add_object(kernel_obj_ptr obj);
            uint32_t duplicate(uint32_t handle);

            kernel_obj_ptr get_object(uint32_t handle);

            bool close(uint32_t handle);

            uint64_t unique_id() {
                return uid;
            }
        };
    }
}