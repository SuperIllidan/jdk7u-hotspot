/*
 * Copyright (c) 2001, 2011, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#ifndef SHARE_VM_GC_IMPLEMENTATION_G1_HEAPREGIONSEQ_INLINE_HPP
#define SHARE_VM_GC_IMPLEMENTATION_G1_HEAPREGIONSEQ_INLINE_HPP

#include "gc_implementation/g1/heapRegion.hpp"
#include "gc_implementation/g1/heapRegionSeq.hpp"

inline size_t HeapRegionSeq::addr_to_index_biased(HeapWord* addr) const {
  assert(_heap_bottom <= addr && addr < _heap_end,
         err_msg("addr: "PTR_FORMAT" bottom: "PTR_FORMAT" end: "PTR_FORMAT,
                 addr, _heap_bottom, _heap_end));
  size_t index = (size_t) addr >> _region_shift;
  return index;
}

inline HeapRegion* HeapRegionSeq::addr_to_region_unsafe(HeapWord* addr) const {
  assert(_heap_bottom <= addr && addr < _heap_end,
         err_msg("addr: "PTR_FORMAT" bottom: "PTR_FORMAT" end: "PTR_FORMAT,
                 addr, _heap_bottom, _heap_end));
  size_t index_biased = addr_to_index_biased(addr);
  HeapRegion* hr = _regions_biased[index_biased];
  assert(hr != NULL, "invariant");
  return hr;
}

inline HeapRegion* HeapRegionSeq::addr_to_region(HeapWord* addr) const {
  if (addr != NULL && addr < _heap_end) {
    assert(addr >= _heap_bottom,
          err_msg("addr: "PTR_FORMAT" bottom: "PTR_FORMAT, addr, _heap_bottom));
    return addr_to_region_unsafe(addr);
  }
  return NULL;
}

inline HeapRegion* HeapRegionSeq::at(size_t index) const {
  assert(index < length(), "pre-condition");
  HeapRegion* hr = _regions[index];
  assert(hr != NULL, "sanity");
  assert(hr->hrs_index() == index, "sanity");
  return hr;
}

#endif // SHARE_VM_GC_IMPLEMENTATION_G1_HEAPREGIONSEQ_INLINE_HPP
