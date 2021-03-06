/*
 * Copyright (c) 2019 EKA2L1 Team.
 * 
 * This file is part of EKA2L1 project.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <epoc/mem/common.h>
#include <epoc/mem/mmu.h>
#include <epoc/mem/page.h>

#include <array>
#include <functional>
#include <memory>

namespace eka2l1 {
    class system;

    namespace mem {
        class mmu_base;
        using mmu_impl = std::unique_ptr<mmu_base>;

        struct page_table_allocator;
        using page_table_allocator_impl = std::unique_ptr<page_table_allocator>;
    }

    namespace arm {
        class arm_interface;
    }

    class memory_system {
        friend class system;

        mem::mmu_impl impl_;
        mem::page_table_allocator_impl alloc_;

        void *rom_map_;
        std::size_t rom_size_;

        mem::vm_address rom_addr_;
        arm::arm_interface *cpu_;

    public:
        explicit memory_system() = default;
        ~memory_system() = default;

        void init(arm::arm_interface *jit, const bool mem_map_old);
        void shutdown();

        mem::mmu_base *get_mmu() {
            return impl_.get();
        }

        const int get_page_size() const;

        void *get_real_pointer(const address addr, const mem::asid optional_asid = -1);

        bool read(const address addr, void *data, uint32_t size);
        bool write(const address addr, void *data, uint32_t size);

        template <typename T>
        T read(const address addr) {
            T data{};
            read(addr, &data, sizeof(T));

            return data;
        }

        template <typename T>
        bool write(const address addr, const T &val) {
            return write(addr, &val, sizeof(T));
        }
    };
}
