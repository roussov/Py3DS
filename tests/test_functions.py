import subprocess
import unittest
import os

class Test3DSFunctions(unittest.TestCase):
    EXECUTABLE = "./3ds"
    TEST_SCRIPT_DIR = "tests/examples"

    def run_script(self, filename):
        path = os.path.join(self.TEST_SCRIPT_DIR, filename)
        result = subprocess.run([self.EXECUTABLE, path], capture_output=True, text=True)
        return result.stdout.strip(), result.returncode

    def test_simple_function(self):
        out, code = self.run_script("simple_function.py")
        self.assertEqual(code, 0)
        self.assertIn("Hello from function", out)

    def test_function_with_args(self):
        out, code = self.run_script("function_args.py")
        self.assertEqual(code, 0)
        self.assertIn("Sum is 15", out)

    def test_recursive_function(self):
        out, code = self.run_script("recursive_factorial.py")
        self.assertEqual(code, 0)
        self.assertIn("Factorial of 5 is 120", out)

    def test_function_return(self):
        out, code = self.run_script("function_return.py")
        self.assertEqual(code, 0)
        self.assertIn("Returned value: 42", out)

if __name__ == "__main__":
    unittest.main()
