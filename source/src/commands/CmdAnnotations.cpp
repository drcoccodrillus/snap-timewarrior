//////////////////////////////////////////////////////////////////////////////
//
//  Copyright , Thomas Lauf, Paul Beckingham, Federico Hernandez.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included
//  in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//  https://www.opensource.org/licenses/mit-license.php
//
//////////////////////////////////////////////////////////////////////////////
//

#include <commands.h>
#include <format.h>
#include <timew.h>
#include <iostream>
#include <IntervalFilterAllWithIds.h>
#include <IntervalFilterAllInRange.h>
#include <IntervalFilterFirstOf.h>

////////////////////////////////////////////////////////////////////////////////
int CmdAnnotations (
  const CLI& cli,
  Rules& rules,
  Database& database,
  Journal& journal)
{
  const bool verbose = rules.getBoolean ("verbose");

  //std::string subcommand = cli.getSubcommand ("add", "remove", "show");

  auto ids = cli.getIds ();
  auto annotation = cli.getAnnotation ();

  journal.startTransaction ();
  flattenDatabase (database, rules);
  std::vector <Interval> intervals;

  if (ids.empty ())
  {
    IntervalFilterFirstOf filtering {std::make_shared <IntervalFilterAllInRange> (Range {})};
    intervals = getTracked (database, rules, filtering);

    if (intervals.empty ())
    {
      throw std::string ("There is no active time tracking.");
    }
    else if (! intervals.at (0).is_open ())
    {
      throw std::string ("At least one ID must be specified. See 'timew help annotations'.");
    }
  }
  else
  {
    auto filtering = IntervalFilterAllWithIds (ids);
    intervals = getTracked (database, rules, filtering);

    if (intervals.size () != ids.size ())
    {
      for (auto& id: ids)
      {
        bool found = false;

        for (auto& interval: intervals)
        {
          if (interval.id == id)
          {
            found = true;
            break;
          }
        }
        if (! found)
        {
          throw format ("ID '@{1}' does not correspond to any tracking.", id);
        }
      }
    }
  }

  // Apply annotation to intervals.
  for (const auto& interval : intervals)
  {
    Interval modified {interval};
    modified.setAnnotation (annotation);

    database.modifyInterval (interval, modified, verbose);

    if (verbose)
    {
      if (annotation.empty ())
      {
        std::cout << "Removed annotation from @" << modified.id << std::endl;
      }
      else
      {
        std::cout << "Annotated @" << modified.id << " with \"" << annotation << "\"" << std::endl;
      }
    }
  }

  journal.endTransaction ();

  return 0;
}

////////////////////////////////////////////////////////////////////////////////