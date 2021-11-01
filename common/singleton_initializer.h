#ifndef SINGLETON_INITIALIZER_INCLUDED
#define SINGLETON_INITIALIZER_INCLUDED

// This singleton is eagerly initialized before main() is called.
// The purpose of this singleton is to explicitly initialize lazily-initialized singletons.
class singleton_initializer_s
{
   public:
      singleton_initializer_s(const singleton_initializer_s &) = delete;
      void operator=(const singleton_initializer_s &) = delete;

      singleton_initializer_s(singleton_initializer_s &&) = delete;
      void operator=(singleton_initializer_s &&) = delete;

      singleton_initializer_s *operator&() = delete;

   private:
      singleton_initializer_s();
      ~singleton_initializer_s();

      static singleton_initializer_s instance;
};

#endif
