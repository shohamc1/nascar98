#!/usr/bin/env python3
"""Emit a diagnostic-only global.c patch for GCC 2.7.2 or 2.8.1."""

import argparse
import difflib
from pathlib import Path

ORDER_ANCHOR = '      qsort (allocno_order, max_allocno, sizeof (int), allocno_compare);\n'
RELOAD_ANCHOR = '  /* Do the reloads now while the allocno data still exist, so that we can\n'
ORDER_TRACE = r'''
      /* Diagnostic only: record the sorted inputs before allocation.  */
      if (file)
        {
          int trace_rank;
          for (trace_rank = 0; trace_rank < max_allocno; trace_rank++)
            {
              int trace_a = allocno_order[trace_rank];
              int trace_priority
                = (((double) (floor_log2 (allocno_n_refs[trace_a])
                              * allocno_n_refs[trace_a])
                    / allocno_live_length[trace_a])
                   * 10000 * allocno_size[trace_a]);
              fprintf (file,
                       ";; n98-order rank=%d allocno=%d pseudo=%d refs=%d "
                       "length=%d size=%d calls=%d priority=%d\n",
                       trace_rank, trace_a, allocno_reg[trace_a],
                       allocno_n_refs[trace_a], allocno_live_length[trace_a],
                       allocno_size[trace_a], allocno_calls_crossed[trace_a],
                       trace_priority);
            }
        }
'''
ASSIGN_TRACE = r'''  /* Diagnostic only: reload may still change these assignments.  */
  if (file)
    {
      int trace_reg;
      for (trace_reg = FIRST_PSEUDO_REGISTER; trace_reg < max_regno;
           trace_reg++)
        fprintf (file,
                 ";; n98-before-reload pseudo=%d allocno=%d hard=%d\n",
                 trace_reg, reg_allocno[trace_reg], reg_renumber[trace_reg]);
    }

'''


def trace_patch(source):
    """Reject an unknown or already instrumented source layout."""
    if 'n98-order' in source or 'n98-before-reload' in source:
        raise ValueError('source already contains the trace')
    for anchor in (ORDER_ANCHOR, RELOAD_ANCHOR):
        if source.count(anchor) != 1:
            raise ValueError('unsupported global.c layout: expected one ' + anchor.strip())
    changed = source.replace(ORDER_ANCHOR, ORDER_ANCHOR + ORDER_TRACE)
    changed = changed.replace(RELOAD_ANCHOR, ASSIGN_TRACE + RELOAD_ANCHOR)
    return ''.join(difflib.unified_diff(
        source.splitlines(keepends=True), changed.splitlines(keepends=True),
        fromfile='a/global.c', tofile='b/global.c'))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path, help='global.c from a private compiler tree')
    args = parser.parse_args()
    try:
        patch = trace_patch(args.source.read_text())
    except (OSError, ValueError) as exc:
        parser.error(str(exc))
    print(patch, end='')


if __name__ == '__main__':
    main()
