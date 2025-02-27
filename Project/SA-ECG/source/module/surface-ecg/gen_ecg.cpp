/**
 * @file gen_ecg.cpp
 *
 * @brief ECG simulator, interfacing with GNU Octave.
 * 
 * -- Versioning Info --
 *
 * v1.0 : 26/02/2025 : Initial working config write-up.
 *
 * @copyright
 * Copyright 2025 British Malaysian Institute, Universiti Kuala Lumpur.
 * 
 * Written by Muhammad Haziq Kamarul Azman a.k.a. Kaiser Haz.
 *******************************************************************************************
 */
 
// Libs
#include "gen_ecg.h"
#include <iostream>
#include <octave/oct.h>
#include <octave/octave.h>
#include <octave/parse.h>
#include <octave/interpreter.h>
#include <octave/error.h>

int gen_ecg()
{

  // Create interpreter.

  octave::interpreter interpreter;

  try
    {
      // Inhibit reading history file by calling
      //
      interpreter.initialize_history (false);

      // Set custom load path here if you wish by calling
      //
      //   interpreter.initialize_load_path (false);

      // Perform final initialization of interpreter, including
      // executing commands from startup files by calling
      //
      //   interpreter.initialize ();
      //
      //   if (! interpreter.is_initialized ())
      //     {
      //       std::cerr << "Octave interpreter initialization failed!"
      //                 << std::endl;
      //       exit (1);
      //     }
      //
      // You may skip this step if you don't need to do anything
      // between reading the startup files and telling the interpreter
      // that you are ready to execute commands.

      // Tell the interpreter that we're ready to execute commands:

      int status = interpreter.execute ();

      if (status != 0)
        {
          std::cerr << "> gen_ecg : creating embedded Octave interpreter failed!"
                    << std::endl;
          return status;
        }
	  
	  std::cout << "> gen_ecg : Executing..." << std::endl;
	  
      octave_value_list out = interpreter.feval ("gen_ecg");
    }
  catch (const octave::exit_exception& ex)
    {
      std::cerr << "> gen_ecg : Octave interpreter exited with status = "
                << ex.exit_status () << std::endl;
	  return -100;
    }
  catch (const octave::execution_exception& ex)
    {
      std::cerr << "> gen_ecg : error encountered in Octave evaluator!" << std::endl;
	  octave::error_system& es = interpreter.get_error_system ();
  
      es.save_exception (ex);
      es.display_exception (ex);
	  
	  return -101;
    }

  return 0;

}
