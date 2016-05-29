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

#ifndef QUANTSYSTEM_COMMON_BASE_EVENT_H_
#define QUANTSYSTEM_COMMON_BASE_EVENT_H_

#include <cstddef>
#include <utility>
using std::pair;
using std::make_pair;
#include <vector>
using std::vector;

namespace quantsystem {

/**
 * One Argumeng Delegate of Quantsystem
 * @ingroup CommonGeneric
 *
 */
template <typename Arg1>
class Delegate {
 public:
  /**
   * Standard constructor.
   */
  Delegate();

  /**
   * Standard destructor.
   */
  virtual ~Delegate();

  /**
   * Bind a free fucntion.
   */
  template <void (*Function)(Arg1)>
  void Bind() {
    stub_.push_back(make_pair((void*)NULL, &FunctionStub<Function>));
  }

  /**
   * Bind a class member function.
   *
   * @param instacne The class instance of the binding function.
   */
  template <class C, void (C::*Function)(Arg1)>
  void Bind(C* instance) {
    stub_.push_back(make_pair(instance, &ClassMethodStub<C, Function>));
  }

  /**
   * Invoke the delegate operation.
   *
   * param arg1 The first argument.
   */
  void operator()(Arg1 arg1) {
    for (typename vector<Stub>::const_iterator it = stub_.begin();
         it != stub_.end(); ++it) {
        it->second(it->first, arg1);
    }
  }

 private:
  typedef void* InstancePtr;
  typedef void (*InternalFunction)(InstancePtr, Arg1);
  typedef pair<InstancePtr, InternalFunction> Stub;
  vector<Stub> stub_;

  template <void (*Function)(Arg1)>
  static void FunctionStub(InstancePtr instance, Arg1 arg1) {
    return (Function)(arg1);
  }

  template <class C, void (C::*Function)(Arg1)>
  static void ClassMethodStub(InstancePtr instance, Arg1 arg1) {
    return (static_cast<C*>(instance)->*Function)(arg1);
  }
};

/**
 * Two Argumeng Delegate of Quantsystem
 * @ingroup CommonGeneric
 *
 */
template <typename Arg1, typename Arg2>
class Delegate2 {
 public:
  /**
   * Standard constructor.
   */
  Delegate2() {};

  /**
   * Standard destructor.
   */
  virtual ~Delegate2() {};

  /**
   * Bind a free fucntion.
   */
  template <void (*Function)(Arg1, Arg2)>
  void Bind() {
    stub_.push_back(make_pair((void*)NULL, &FunctionStub<Function>));
  }

  /**
   * Bind a class member function.
   *
   * @param instacne The class instance of the binding function.
   */
  template <class C, void (C::*Function)(Arg1, Arg2)>
  void Bind(C* instance) {
    stub_.push_back(make_pair(instance, &ClassMethodStub<C, Function>));
  }

  /**
   * Invoke the delegate operation.
   *
   * param arg1 The first argument.
   */
  void operator()(Arg1 arg1, Arg2 arg2) {
    for (typename vector<Stub>::const_iterator it = stub_.begin();
         it != stub_.end(); ++it) {
      it->second(it->first, arg1, arg2);
    }
  }

 private:
  typedef void* InstancePtr;
  typedef void (*InternalFunction)(InstancePtr, Arg1, Arg2);
  typedef pair<InstancePtr, InternalFunction> Stub;
  vector<Stub> stub_;

  template <void (*Function)(Arg1, Arg2)>
  static void FunctionStub(InstancePtr instance, Arg1 arg1, Arg2 arg2) {
    return (Function)(arg1, arg2);
  }

  template <class C, void (C::*Function)(Arg1, Arg2)>
  static void ClassMethodStub(InstancePtr instance, Arg1 arg1, Arg2 arg2) {
    return (static_cast<C*>(instance)->*Function)(arg1, arg2);
  }
};

}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_BASE_EVENT_H_
