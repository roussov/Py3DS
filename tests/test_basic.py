import subprocess
import unittest
import os

class Test3DSBasic(unittest.TestCase):
    EXECUTABLE = "./3ds"
    TEST_SCRIPT_DIR = "tests/examples"

    def run_script(self, filename):
        """Lance un script via l’interpréteur et retourne la sortie stdout."""
        path = os.path.join(self.TEST_SCRIPT_DIR, filename)
        result = subprocess.run([self.EXECUTABLE, path], capture_output=True, text=True)
        return result.stdout.strip(), result.returncode

    def test_print_hello(self):
        out, code = self.run_script("hello.py")
        self.assertEqual(code, 0)
        self.assertIn("Hello, world!", out)

    def test_arithmetic(self):
        out, code = self.run_script("arithmetic.py")
        self.assertEqual(code, 0)
        self.assertIn("Result: 42", out)

    def test_syntax_error(self):
        out, code = self.run_script("syntax_error.py")
        self.assertNotEqual(code, 0)
        self.assertIn("Syntax error", out)

    def test_variable_assignment(self):
        out, code = self.run_script("variables.py")
        self.assertEqual(code, 0)
        self.assertIn("x = 10", out)

if __name__ == "__main__":
    unittest.main()
