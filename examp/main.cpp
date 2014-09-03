/* -8- ***********************************************************************
 *
 *  main.cpp
 *
 *                                          Created by ogata on 11/26/2013
 *                 Copyright (c) 2013 ABEJA Inc. All rights reserved.
 * ******************************************************************** -8- */

#include "cspxlog.h"

void test_logging()
{
  boost::log::sources::severity_logger< cspxlog::severity_level > slg;
  BOOST_LOG_FUNCTION();
  BOOST_LOG_SEV(slg, cspxlog::ERROR) << "test";
}

void test_logging2()
{
  boost::log::sources::severity_logger< cspxlog::severity_level > slg;
  BOOST_LOG_SEV(slg, cspxlog::ERROR) << "test2";
}

void test_setLoggingLevel()
{
  BOOST_LOG_FUNCTION();
  std::cout << "---- start test_setLoggingLevel ----" << std::endl;
  BOOST_LOG_SEV(app_logger::get(), cspxlog::DEBUG) << "first debug";
  BOOST_LOG_SEV(app_logger::get(), cspxlog::TRACE) << "first trace";

  std::cout << "set filter level \"DEBUG\"" << std::endl;
  cspxlog::setLoggingLevel(cspxlog::DEBUG);

  BOOST_LOG_SEV(app_logger::get(), cspxlog::DEBUG) << "second debug"; // printed
  BOOST_LOG_SEV(app_logger::get(), cspxlog::TRACE) << "second trace"; // filtered
  std::cout << "---- end test_setLoggingLevel ----" << std::endl;
}

int main(int argc, char *argv[])
{
  // initalize
  cspxlog::initLogging();

  // set __LINE__ and __FUNCTION__
  BOOST_LOG_FUNCTION();

  test_logging();
  test_logging2();
  
  test_setLoggingLevel();

  std::cout << "---- end ----" << std::endl;
  return 0;
}
