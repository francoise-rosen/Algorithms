//
//  naiveCounter.h
//  frequencyCounter
//
//  Created by syfo_dias on 13/02/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#ifndef naiveCounter_h
#define naiveCounter_h
#include <vector>

namespace sfd
{
    /** Naive - quadratic time. */
    bool frequencyCounterNaive (const std::vector<int>& arr1, const std::vector<int>& arr2)
    {
        if (arr1.size() != arr2.size())
            return false;
        
        std::vector<bool> visited (arr2.size(), false);
        bool match = false;
        for (auto elem : arr1)
        {
            for (int i = 0; i < arr2.size(); ++i)
            {
                if (elem * elem == arr2[i])
                {
                    if (! visited[i])
                    {
                        visited[i] = true;
                        match = true;
                        break;
                    }
                }
                else
                    match = false;
            }
            if (match == false)
                return false;
        }
        return true;
    }
}

#endif /* naiveCounter_h */
