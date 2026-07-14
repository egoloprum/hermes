#include <iostream>

import Hermes;

int main() {
  Hermes::HermesFactory app;

  app.route("/auth", authRoutes);
  app.route("/posts", postsRoutes);
  app.route("/users", usersRoutes);

  Server server { app, "3001" };
  server.run();

  return 0;
}
