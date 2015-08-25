from subprocess import call

# Do some cleanup
call(["clear"])             # Clear the screen
call(["make", "clean"])     # Clean everything
call(["make", "-j6"])       # Make the executable (which will run it