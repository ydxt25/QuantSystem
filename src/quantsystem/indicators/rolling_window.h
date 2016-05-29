/*
 * \copyright Copyright 2015 All Rights Reserved.
 * \license @{
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @}
 */

#ifndef QUANTSYSTEM_INDICATORS_ROLLING_WINDOW_H_
#define QUANTSYSTEM_INDICATORS_ROLLING_WINDOW_H_

#include <vector>
using std::vector;
#include <glog/logging.h>
#include "quantsystem/indicators/iread_only_window.h"
namespace quantsystem {
namespace indicators {
/**
 * This is a window that allows for list access semantics,
 * where this[0] refers to the most recent item in the
 * window and this[Count-1] refers to the last item in the window
 * @ingroup IndicatorsLayer
 */
template <typename T>
class RollingWindow : public IReadOnlyWindow<T> {
 public:
  /**
   * Initializes a new instance of the RollwingWindow class
   * with the specified window size.
   * @param size The  number of items to hold in the window
   */
  explicit RollingWindow(int size) {
    const int kDefaultSize = 10;
    if (size < 1) {
      LOG(FATAL) << "RollingWindow must have size of at least 1." << size;
      size = kDefaultSize;
    }
    list_.resize(size);
  }

  /**
   * Gets the size of this window.
   */
  int Size() const {
    return list_.size();
  }

  /**
   * Gets the current number of elements in this window
   */
  int Count() const { return count_; }

  /**
   * Gets the number of samples that have been added to this window
   * over its lifetime.
   */
  double samples() const { return samples_; }

  /**
   * Gets the most recently removed item from the window. This is the piece
   * of data that just 'fell off' as a result of the most recent add.
   */
  T most_recently_removed() const {
    if (!is_ready()) {
      LOG(FATAL) << "No items have been removed yet!";
    }
    return most_recently_removed_;
  }

  /**
   * Indexes into this window, where index 0 is the most recently entered value.
   * @param i THe index
   * @return The ith most recent entry
   */
  virtual T operator[] (int i) const {
  }

  /**
   * Gets a value indicating whether or not this window is ready, i.e,
   * it has been filled to its capacity and one has fallen off the back.
   */
  bool is_ready() const {
    return samples() > Size();
  }

  /**
   * Adds an item to this window and shifts all other elements.
   * @param item The item to be added.
   */
  void Add(const T& item) {
  }

  /**
   * Clears this window of all data.
   */
  void Reset() {
    samples_ = 0;
    list_.clear();
  }

 private:
  // The backing vector object used to hold the data
  vector<T> list_;
  // The most recently removed item from the window (fell off the back)
  T most_recently_removed_;
  // The total number of samples taken by this indicator
  double samples_;
  // Used to locate the last item in the window as an indexer into the list_
  int tail_;
  // The current number of elements in this window
  int count_;
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_ROLLING_WINDOW_H_
