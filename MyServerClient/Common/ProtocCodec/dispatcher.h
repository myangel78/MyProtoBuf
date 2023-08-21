#include "query.pb.h"

#include <iostream>     // std::cout
#include <functional>   // std::function, std::negate
#include "noncopyable.h"
#include <memory>


using namespace std;

class Callback : muduo::noncopyable
{
 public:
  virtual ~Callback() {};
  virtual void onMessage(google::protobuf::Message* message) const = 0;
};


template <typename T>
class CallbackT : public Callback
{
 public:
  typedef std::function<void (T* message)> ProtobufMessageCallback;

  CallbackT(const ProtobufMessageCallback& callback)
    : callback_(callback)
  {
  }

  virtual void onMessage(google::protobuf::Message* message) const
  {
    T* t = dynamic_cast<T*>(message);
    assert(t != NULL);
    callback_(t);
  }

 private:
  ProtobufMessageCallback callback_;
};

void discardProtobufMessage(google::protobuf::Message* message)
{
  cout << "Discarding " << message->GetTypeName() << endl;
}

class ProtobufDispatcher
{
 public:

  ProtobufDispatcher()
    : defaultCallback_(discardProtobufMessage)
  {
  }

  void onMessage(google::protobuf::Message* message) const
  {
    CallbackMap::const_iterator it = callbacks_.find(message->GetDescriptor());
    if (it != callbacks_.end())
    {
      it->second->onMessage(message);
    }
    else
    {
      defaultCallback_(message);
    }
  }

  template<typename T>
  void registerMessageCallback(const typename CallbackT<T>::ProtobufMessageCallback& callback)
  {
      std::shared_ptr<CallbackT<T> > pd(new CallbackT<T>(callback));
    callbacks_[T::descriptor()] = pd;
  }

  typedef std::map<const google::protobuf::Descriptor*, std::shared_ptr<Callback>> CallbackMap;
  CallbackMap callbacks_;
  std::function<void (google::protobuf::Message* message)> defaultCallback_;
};

//
// test
//

void onQuery(muduo::Query* query)
{
  cout << "onQuery: " << query->GetTypeName() << endl;
}

void onAnswer(muduo::Answer* answer)
{
  cout << "onAnswer: " << answer->GetTypeName() << endl;
}

//int main()
//{
//  ProtobufDispatcher dispatcher;
//  dispatcher.registerMessageCallback<muduo::Query>(onQuery);
//  dispatcher.registerMessageCallback<muduo::Answer>(onAnswer);
//
//  muduo::Query q;
//  muduo::Answer a;
//  muduo::Empty e;
//  dispatcher.onMessage(&q);
//  dispatcher.onMessage(&a);
//  dispatcher.onMessage(&e);
//
//  google::protobuf::ShutdownProtobufLibrary();
//}
