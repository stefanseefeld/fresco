/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999-2003 Tobias Hunger <Tobias@fresco.org>
 * http://www.fresco.org
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA.
 */

#ifndef _Babylon_internal_utils_hh
#define _Babylon_internal_utils_hh

// ---------------------------------------------------------------------------
// Helperfunctions for Bidir:
// ---------------------------------------------------------------------------

namespace Babylon {

  inline bool bidir_is_strong(const Babylon::Bidir_Props & p)
  {
      return (p & Babylon::BIDIR_MASK_STRONG);
  }

  inline bool bidir_is_neutral(const Babylon::Bidir_Props & p)
  {
      return (p & Babylon::BIDIR_MASK_NEUTRAL);
  }

  inline bool bidir_is_explicit_or_bn(const Babylon::Bidir_Props & p)
  {
      return (p & (BIDIR_MASK_EXPLICIT | BIDIR_MASK_BN));
  }

  inline bool bidir_is_letter(const Babylon::Bidir_Props & p)
  {
      return (p & Babylon::BIDIR_MASK_LETTER);
  }

  inline bool bidir_is_number(const Babylon::Bidir_Props & p)
  {
      return (p & Babylon::BIDIR_MASK_NUMBER);
  }

  inline bool bidir_is_override(const Babylon::Bidir_Props & p)
  {
      return (p & Babylon::BIDIR_MASK_OVERRIDE);
  }

  inline bool bidir_is_ES_or_CS(const Babylon::Bidir_Props & p)
  {
      return (p & (Babylon::BIDIR_MASK_ES | Babylon::BIDIR_MASK_CS));
  }

  inline bool bidir_is_separator(const Babylon::Bidir_Props & p)
  {
      return (p & Babylon::BIDIR_MASK_SEPARATOR);
  }

  inline Babylon::Bidir_Props
  bidir_change_number_to_RTL(const Babylon::Bidir_Props &p)
  {
      return (bidir_is_number(p) ? Babylon::BIDIR_R : p);
  }

  inline bool
  bidir_is_explicit_or_separator_or_BN_or_WS(const Babylon::Bidir_Props & p)
  {
      return (p & (Babylon::BIDIR_MASK_EXPLICIT |
           Babylon::BIDIR_MASK_SEPARATOR |
           Babylon::BIDIR_MASK_BN |
           Babylon::BIDIR_MASK_WS));
  }

  inline bool
  bidir_is_number_separator_or_terminator(const Babylon::Bidir_Props & p)
  {
      return (p & Babylon::BIDIR_MASK_NUMSEPTER);
  }

  inline bool bidir_is_PDF(const Babylon::Bidir_Props & p)
  {
      return (p == BIDIR_PDF);
  }

  inline unsigned char bidir_to_level(const Babylon::Bidir_Props&  p)
  {
      return (p & 1);
  }

  inline Babylon::Bidir_Props level_to_bidir(const unsigned char lev)
  {
      return (Babylon::Bidir_Props(Babylon::BIDIR_L | (lev & 1)));
  }

  inline Babylon::Bidir_Props
  bidir_explicit_to_override_dir(const Babylon::Bidir_Props & p)
  {
      return (bidir_is_override(p) ?
          level_to_bidir(bidir_to_level(p)) : 
          BIDIR_ON);
  }

  inline bool compact(const Babylon::Embedding_Level & a,
              const Babylon::Embedding_Level & b)
  {
      return (a.bidir_type == b.bidir_type && a.level == b.level);
  }

  inline bool compact_neutrals(const Babylon::Embedding_Level & a,
                   const Babylon::Embedding_Level & b)
  {
      return (a.level == b.level &&
          (a.bidir_type == b.bidir_type ||
           bidir_is_neutral(a.bidir_type) &&
           bidir_is_neutral(b.bidir_type)));
  }

  inline Babylon::Bidir_Props change_number_to_rtl(Babylon::Bidir_Props p)
  {
      return (bidir_is_number(p) ? Babylon::BIDIR_R : p);
  }


  Embedding_Levels::iterator
  compact(const Embedding_Levels::iterator & start,
      const Embedding_Levels::iterator & end)
  {
      Prague::Trace trace("Babylon::compact(...)");
      if (start == end) return(end);
      
      Embedding_Levels::iterator last_used = start;
      Embedding_Levels::iterator current = start;
      ++current;
      
      while(current != end)
      {
      if (last_used->level == current->level &&
          last_used->bidir_type == current->bidir_type)
          last_used->increment_length(current->length());
      else
      {
          ++last_used;
          std::iter_swap(last_used, current);
      }
      ++current;
      }
      
      return (++last_used);
  }

  Embedding_Levels::iterator
  compact_neutrals(const Embedding_Levels::iterator & start,
           const Embedding_Levels::iterator & end)
  {
      Prague::Trace trace("Babylon::compact_neutrals(...)");
      if (start == end) return (end);
      
      Embedding_Levels::iterator last_used = start;
      Embedding_Levels::iterator current = start;
      ++current;
      
      while(current != end)
      {
      if (last_used->level == current->level &&
          (last_used->bidir_type == current->bidir_type ||
           bidir_is_neutral(last_used->bidir_type) &&
           bidir_is_neutral(current->bidir_type)))
          last_used->increment_length(current->length());
      else
      {
          ++last_used;
          std::iter_swap(last_used, current);
      }
      ++current;
      }

      return(++last_used);
  }

  Embedding_Levels
  override_lists(const Embedding_Levels & base,
         const Embedding_Levels & over)
  {
      Prague::Trace trace("Babylon::override_lists(...)");
      if (base.empty()) return (over);
      if (over.empty()) return (base);
      
      Embedding_Levels::const_iterator over_it = over.begin();
      Embedding_Levels::const_iterator base_it = base.begin();
      
      Embedding_Levels result;
      
      while(!(over_it == over.end() && base_it == base.end()))
      {
      // One list is empty, copy the other over:
      if (over_it == over.end())
      {
          // copy base
          std::copy(base_it, base.end(),
            std::back_inserter(result));
          base_it = base.end();
          continue;
      }
      
      if (base_it == base.end())
      {
          // copy over
          std::copy(over_it, over.end(),
            std::back_inserter(result));
          over_it = over.end();
          continue;
      }
      
      // skip invalid entries
      if (over_it->length() == 0)
      {
          ++over_it;
          continue;
      }
      
      if (base_it->length() == 0)
      {
          ++base_it;
          continue;
      }
    
      size_t max_current = base_it->ends_at();
      
      // copying base:
      if (max_current < over_it->starts_at())
      {
          result.push_back(*base_it);
          ++base_it;
          continue;
      }
      
      // inserting over_it into base_it
      if (max_current >= over_it->starts_at())
      {
          Babylon::Embedding_Level current = *base_it;
          
          // Insert first part of base if not empty:
          current.length(over_it->starts_at() - current.starts_at());
          if (current.length() != 0)
          // current.length can't become < 0 as
          // max_current >= over_it.start
          result.push_back(current);
          
          // Insert over_it (we always need to do this!)
          result.push_back(*over_it);
          
          // over_it reaches into the next base_it:
          while (base_it != base.end() &&
             base_it->ends_at() < over_it->ends_at())
          ++base_it;

          if (base_it == base.end()) continue;
          
          current = *base_it;
          current.length(current.ends_at() - over_it->ends_at());
          current.starts_at(over_it->ends_at() + 1);
          ++base_it;
          ++over_it;
          continue;
      }
      } // while
      
      return (result);
  }

}; // namespace Babylon

#endif
