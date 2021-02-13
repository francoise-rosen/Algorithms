//
//  subZero.h
//  multiplePointers
//
//  Created by syfo_dias on 13/02/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#ifndef subZero_h
#define subZero_h

template <typename C, typename Iter = typename C::const_iterator, typename T = typename C::value_type>
std::pair<Iter, Iter> subZero (const C& container)
{
    Iter first = container.begin();
    Iter last = container.end();
    Iter back = last;
    --back;
    while (first != back)
    {
        if ((*first) + (*back) == 0)
            return std::pair<Iter, Iter> (first, back);
        if ((*first) + (*back) < 0)
            ++first;
        else if ((*first) + (*back) > 0)
            --back;
    }
    return std::pair<Iter, Iter> (last, last);
}
#endif /* subZero_h */
