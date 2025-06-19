import subprocess
import unittest
import os

class Test3DSControlFlow(unittest.TestCase):
    EXECUTABLE = "./3ds"
    TEST_SCRIPT_DIR = "tests/examples"

    def run_script(self, filename):
        path = os.path.join(self.TEST_SCRIPT_DIR, filename)
        result = subprocess.run([self.EXECUTABLE, path], capture_output=True, text=True)
        return result.stdout.strip(), result.returncode

    def test_if_else(self):
        out, code = self.run_script("if_else.py")
        self.assertEqual(code, 0)
        self.assertIn("Condition true", out)
        self.assertNotIn("Condition false", out)

    def test_while_loop(self):
        out, code = self.run_script("while_loop.py")
        self.assertEqual(code, 0)
        self.assertIn("Count: 0", out)
        self.assertIn("Count: 4", out)
        self.assertNotIn("Count: 5", out)

    def test_for_loop(self):
        out, code = self.run_script("for_loop.py")
        self.assertEqual(code, 0)
        self.assertIn("Sum is 10", out)

    def test_function_call(self):
        out, code = self.run_script("function_call.py")
        self.assertEqual(code, 0)
        self.assertIn("Result: 6", out)

if __name__ == "__main__":
    unittest.main()
