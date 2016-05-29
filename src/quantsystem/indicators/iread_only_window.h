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

#ifndef QUANTSYSTEM_INDICATORS_IREADY_ONLY_WINDOW_H_
#define QUANTSYSTEM_INDICATORS_IREADY_ONLY_WINDOW_H_

namespace quantsystem {
namespace indicators {
/**
 * Interface type used to pass windows around without
 * worrying of external modification
 * @ingroup IndicatorsLayer
 */
template <typename T>
class IReadOnlyWindow {
 public:
  int size() const { return size_; }

  int count() const { return count_; }

  double smaples() const { return samples_; }

  bool is_ready() const { return is_ready_; }

  /**
   * Gets the most recently removed item from the window. This is the piece
   * of data that just 'fell off' as a result of the most recent add.
   */
  T most_recently_removed() const { return most_recently_removed_; }

  /**
   * Indexes into this window, where index 0 is the most recently entered value.
   * @param i THe index
   * @return The ith most recent entry
   */
  virtual T operator[] (int i) const = 0;

 private:
  // The size of this window
  int size_;
  // The current number of elements in this window
  int count_;
  // The number of samples that have been added to this window over its lifetime
  double samples_;
  // Indicating whether or not this window is ready
  bool is_ready_;
  // The most recently removed item from the window
  T most_recently_removed_;
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_IREADY_ONLY_WINDOW_H_
