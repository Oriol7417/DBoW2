/**
 * File: FORB.cpp
 * Date: June 2012
 * Author: Dorian Galvez-Lopez
 * Description: functions for ORB descriptors
 * License: see the LICENSE.txt file
 *
 */
 
#include <vector>
#include <string>
#include <sstream>
#include <stdint.h>
#include <limits.h>

#include "FORB2.h"

using namespace std;

namespace DBoW2 {

int ones8bits[256] = 
{
  0, // 0
  1, // 1
  1, // 2
  2, // 3
  1, // 4
  2, // 5
  2, // 6
  3, // 7
  1, // 8
  2, // 9
  2, // 10
  3, // 11
  2, // 12
  3, // 13
  3, // 14
  4, // 15
  1, // 16
  2, // 17
  2, // 18
  3, // 19
  2, // 20
  3, // 21
  3, // 22
  4, // 23
  2, // 24
  3, // 25
  3, // 26
  4, // 27
  3, // 28
  4, // 29
  4, // 30
  5, // 31
  1, // 32
  2, // 33
  2, // 34
  3, // 35
  2, // 36
  3, // 37
  3, // 38
  4, // 39
  2, // 40
  3, // 41
  3, // 42
  4, // 43
  3, // 44
  4, // 45
  4, // 46
  5, // 47
  2, // 48
  3, // 49
  3, // 50
  4, // 51
  3, // 52
  4, // 53
  4, // 54
  5, // 55
  3, // 56
  4, // 57
  4, // 58
  5, // 59
  4, // 60
  5, // 61
  5, // 62
  6, // 63
  1, // 64
  2, // 65
  2, // 66
  3, // 67
  2, // 68
  3, // 69
  3, // 70
  4, // 71
  2, // 72
  3, // 73
  3, // 74
  4, // 75
  3, // 76
  4, // 77
  4, // 78
  5, // 79
  2, // 80
  3, // 81
  3, // 82
  4, // 83
  3, // 84
  4, // 85
  4, // 86
  5, // 87
  3, // 88
  4, // 89
  4, // 90
  5, // 91
  4, // 92
  5, // 93
  5, // 94
  6, // 95
  2, // 96
  3, // 97
  3, // 98
  4, // 99
  3, // 100
  4, // 101
  4, // 102
  5, // 103
  3, // 104
  4, // 105
  4, // 106
  5, // 107
  4, // 108
  5, // 109
  5, // 110
  6, // 111
  3, // 112
  4, // 113
  4, // 114
  5, // 115
  4, // 116
  5, // 117
  5, // 118
  6, // 119
  4, // 120
  5, // 121
  5, // 122
  6, // 123
  5, // 124
  6, // 125
  6, // 126
  7, // 127
  1, // 128
  2, // 129
  2, // 130
  3, // 131
  2, // 132
  3, // 133
  3, // 134
  4, // 135
  2, // 136
  3, // 137
  3, // 138
  4, // 139
  3, // 140
  4, // 141
  4, // 142
  5, // 143
  2, // 144
  3, // 145
  3, // 146
  4, // 147
  3, // 148
  4, // 149
  4, // 150
  5, // 151
  3, // 152
  4, // 153
  4, // 154
  5, // 155
  4, // 156
  5, // 157
  5, // 158
  6, // 159
  2, // 160
  3, // 161
  3, // 162
  4, // 163
  3, // 164
  4, // 165
  4, // 166
  5, // 167
  3, // 168
  4, // 169
  4, // 170
  5, // 171
  4, // 172
  5, // 173
  5, // 174
  6, // 175
  3, // 176
  4, // 177
  4, // 178
  5, // 179
  4, // 180
  5, // 181
  5, // 182
  6, // 183
  4, // 184
  5, // 185
  5, // 186
  6, // 187
  5, // 188
  6, // 189
  6, // 190
  7, // 191
  2, // 192
  3, // 193
  3, // 194
  4, // 195
  3, // 196
  4, // 197
  4, // 198
  5, // 199
  3, // 200
  4, // 201
  4, // 202
  5, // 203
  4, // 204
  5, // 205
  5, // 206
  6, // 207
  3, // 208
  4, // 209
  4, // 210
  5, // 211
  4, // 212
  5, // 213
  5, // 214
  6, // 215
  4, // 216
  5, // 217
  5, // 218
  6, // 219
  5, // 220
  6, // 221
  6, // 222
  7, // 223
  3, // 224
  4, // 225
  4, // 226
  5, // 227
  4, // 228
  5, // 229
  5, // 230
  6, // 231
  4, // 232
  5, // 233
  5, // 234
  6, // 235
  5, // 236
  6, // 237
  6, // 238
  7, // 239
  4, // 240
  5, // 241
  5, // 242
  6, // 243
  5, // 244
  6, // 245
  6, // 246
  7, // 247
  5, // 248
  6, // 249
  6, // 250
  7, // 251
  6, // 252
  7, // 253
  7, // 254
  8  // 255
};

// --------------------------------------------------------------------------

void FORB2::meanValue(const std::vector<FORB2::pDescriptor> &descriptors, 
  FORB2::TDescriptor &mean)
{
  if(descriptors.empty())
  {
    return;
  }
  else if(descriptors.size() == 1)
  {
    mean = *descriptors[0];
  }
  else
  {
    vector<int> sum(FORB2::L * 8, 0);
    
    for(auto it = descriptors.begin(); it != descriptors.end(); ++it)
    {
      const FORB2::TDescriptor &desc = **it;
      for(int i = 0; i < FORB2::L; i++)
      {
        if(desc[i] & (1 << 7)) ++sum[ i*8     ];
        if(desc[i] & (1 << 6)) ++sum[ i*8 + 1 ];
        if(desc[i] & (1 << 5)) ++sum[ i*8 + 2 ];
        if(desc[i] & (1 << 4)) ++sum[ i*8 + 3 ];
        if(desc[i] & (1 << 3)) ++sum[ i*8 + 4 ];
        if(desc[i] & (1 << 2)) ++sum[ i*8 + 5 ];
        if(desc[i] & (1 << 1)) ++sum[ i*8 + 6 ];
        if(desc[i] & (1))      ++sum[ i*8 + 7 ];
      }
    }

    mean = vector<uint8_t>(FORB2::L, 0);
    
    int j = 0; 
    const int N2 = (int)descriptors.size() / 2 + descriptors.size() % 2;
    for(size_t i = 0; i < sum.size(); ++i)
    {
      if(sum[i] >= N2)
      {
        // set bit
        mean[j] |= 1 << (7 - (i % 8));
      }
      
      if(i % 8 == 7) ++j;
    }
  }
}

// --------------------------------------------------------------------------
  
double FORB2::distance(const FORB2::TDescriptor &a, 
  const FORB2::TDescriptor &b)
{
  // If uint64_t is not defined in your system, you can try this 
  // portable approach (requires DUtils from DLib)
  int ret = 0;
  for(int i = 0; i < FORB2::L; i++)
  {
    ret += ones8bits[ a[i] ^ b[i] ];
  }
   
  return ret;
}

// --------------------------------------------------------------------------
  
std::string FORB2::toString(const FORB2::TDescriptor &a)
{
  stringstream ss;
  for(int i = 0; i < FORB2::L; i++)
  {
    ss << (int)a[i] << " ";
  }
  
  return ss.str();
}

// --------------------------------------------------------------------------
  
void FORB2::fromString(FORB2::TDescriptor &a, const std::string &s)
{
  a.resize(FORB2::L);
  
  stringstream ss(s);
  for(int i = 0; i < FORB2::L; i++)
  {
    int n;
    ss >> n;
    
    if(!ss.fail()) 
      a[i] = (unsigned char)n;
  }
  
}

// --------------------------------------------------------------------------

} // namespace DBoW2

