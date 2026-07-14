#include "lib/exception-base.hpp"

class SocketException : public FrameworkException {};
class SocketCreationException : public FrameworkException {};
class SocketBindException : public FrameworkException {};
class SocketListenException : public FrameworkException {};
class SocketAcceptException : public FrameworkException {};
class SocketReceiveException : public FrameworkException {};
class SocketSendException : public FrameworkException {};
class SocketShutdownException : public FrameworkException {};
class SocketCloseException : public FrameworkException {};
