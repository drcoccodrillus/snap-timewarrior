////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2015 - 2016, Paul Beckingham, Federico Hernandez.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// http://www.opensource.org/licenses/mit-license.php
//
////////////////////////////////////////////////////////////////////////////////

#include <cmake.h>
#include <Duration.h>
#include <format.h>
#include <commands.h>
#include <timew.h>
#include <iostream>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
int CmdJoin (
  const CLI& cli,
  Rules& rules,
  Database& database)
{
  // Gather IDs and TAGs.
  std::vector <int> ids;
  for (auto& arg : cli._args)
    if (arg.hasTag ("ID"))
      ids.push_back (strtol (arg.attribute ("value").c_str (), NULL, 10));

  // Load the data.
  // Note: There is no filter.
  Interval filter;
  auto tracked = getTracked (database, rules, filter);

  // Only 2 IDs allowed in a join.
  if (ids.size () != 2)
    throw std::string ("Two IDs must be specified. See 'timew help join'.");

  // ID values must be in range.
  for (auto& id : ids)
    if (id > static_cast <int> (tracked.size ()))
      throw format ("ID '@{1}' does not correspond to any tracking.", id);

  auto first_id  = std::max (ids[0], ids[1]);
  auto second_id = std::min (ids[0], ids[1]);
  Interval first  = tracked[tracked.size () - first_id];
  Interval second = tracked[tracked.size () - second_id];

  // TODO Require confirmation if intervals are not consecutive.
  // TODO Require confirmation if tags don't match.

  auto combined = first;
  combined.range.end = second.range.end;

  database.deleteInterval (first);
  database.deleteInterval (second);

  validate (cli, rules, database, combined);
  database.addInterval (combined);

  if (rules.getBoolean ("verbose"))
    std::cout << "Joined @" << ids[0] << " and @" << ids[1] << '\n';

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
