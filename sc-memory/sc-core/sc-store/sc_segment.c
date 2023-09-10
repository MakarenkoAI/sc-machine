/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "sc_segment.h"

#include "sc_element.h"

#include "sc-base/sc_allocator.h"
#include "sc-base/sc_atomic.h"

sc_segment * sc_segment_new(sc_addr_seg num)
{
  sc_segment * segment = sc_mem_new(sc_segment, 1);
  segment->num = num;
  segment->elements_count = 0;

  return segment;
}

void sc_segment_free(sc_segment * segment)
{
  sc_mem_free(segment);
}

void sc_segment_collect_elements_stat(sc_segment * seg, sc_stat * stat)
{
  for (sc_int32 i = 0; i < seg->elements_count; ++i)
  {
    sc_type type = seg->elements[i].flags.type;
    if (type & sc_type_node)
      stat->node_count++;
    else if (type & sc_type_link)
      stat->link_count++;
    else if (type & sc_type_arc_mask)
      stat->arc_count++;
  }
}

// ---------------------------

sc_element * sc_segment_lock_element(sc_segment * seg, sc_addr_offset offset)
{
  return &seg->elements[offset - 1];
}

sc_element * sc_segment_lock_element_try(sc_segment * seg, sc_addr_offset offset, sc_uint16 max_attempts)
{
  return &seg->elements[offset - 1];
}

void sc_segment_unlock_element(sc_segment * seg, sc_addr_offset offset)
{
}
