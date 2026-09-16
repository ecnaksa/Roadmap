"""
#13 - PRUEBAS UNITARIAS

=========================== TEORÍA ===========================
Las PRUEBAS UNITARIAS verifican, de forma automática y aislada, que una
unidad de código (una función, un método) se comporta como se espera.
Aportan confianza al refactorizar y documentan el comportamiento esperado.

Python incluye el módulo `unittest`:
  - Se crea una clase que hereda de unittest.TestCase.
  - Cada método `test_*` es una prueba.
  - Se comprueban condiciones con assertEqual, assertTrue, assertIn, etc.

Ejecuta:  python ecnaksa.py        (lanza los tests)
"""

import unittest


# --------- Código bajo prueba ---------


def sumar(a: float, b: float) -> float:
    return a + b


PERFIL = {
    "name": "ecnaksa",
    "age": "30",
    "birth_date": "1994-05-12",
    "programming_languages": ["Python", "JavaScript", "Rust"],
}


# --------- Tests ---------


class TestSumar(unittest.TestCase):
    def test_suma_positivos(self):
        self.assertEqual(sumar(2, 3), 5)

    def test_suma_negativos(self):
        self.assertEqual(sumar(-2, -3), -5)

    def test_suma_decimales(self):
        self.assertAlmostEqual(sumar(0.1, 0.2), 0.3, places=7)


class TestPerfil(unittest.TestCase):
    CAMPOS = ("name", "age", "birth_date", "programming_languages")

    def test_existen_todos_los_campos(self):
        for campo in self.CAMPOS:
            self.assertIn(campo, PERFIL, f"Falta el campo {campo}")

    def test_datos_correctos(self):
        self.assertIsInstance(PERFIL["name"], str)
        self.assertTrue(PERFIL["name"])                       # no vacío
        self.assertTrue(PERFIL["age"].isdigit())              # edad numérica
        self.assertRegex(PERFIL["birth_date"], r"^\d{4}-\d{2}-\d{2}$")
        self.assertIsInstance(PERFIL["programming_languages"], list)
        self.assertGreater(len(PERFIL["programming_languages"]), 0)


if __name__ == "__main__":
    unittest.main(verbosity=2)
