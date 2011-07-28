
#include <dtkCore/dtkSingleton.h>

/* Commentary:
*/

/**
 * Code example :
 * \code
Example usage:

{ mySingleton.h }

    #include <dtkCore/dtkSingletoneDeclare.h>

    class MySingleton
    {
        // declares MySingleton::instance()
        DTK_DECLARE_SINGLETON( MySingleton );

        public:

        protected:
        // hide the constructor
        MySingleton() {};
        ~MySingleton() {};

        // class method example
        void doSomething() {...};

        private:
    };

{ mySingleton.cpp }

#include <dtkCore/dtkSingleton>

DTK_IMPLEMENT_SINGLETON( MySingleton );

 */

