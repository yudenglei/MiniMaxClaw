import pytest
import pymylib


class TestCalculator:
    def test_add(self):
        calc = pymylib.Calculator()
        assert calc.add(1, 2) == 3
        assert calc.add(-1, 1) == 0
        assert calc.add(0.1, 0.2) == pytest.approx(0.3)
    
    def test_subtract(self):
        calc = pymylib.Calculator()
        assert calc.subtract(5, 3) == 2
        assert calc.subtract(0, 0) == 0
    
    def test_multiply(self):
        calc = pymylib.Calculator()
        assert calc.multiply(3, 4) == 12
        assert calc.multiply(-2, 3) == -6
    
    def test_divide(self):
        calc = pymylib.Calculator()
        assert calc.divide(10, 2) == 5
        assert calc.divide(1, 2) == pytest.approx(0.5)
    
    def test_divide_by_zero(self):
        calc = pymylib.Calculator()
        with pytest.raises(ValueError):
            calc.divide(1, 0)
    
    def test_compute_stats(self):
        calc = pymylib.Calculator()
        result = calc.compute_stats([1, 2, 3, 4, 5])
        assert result.value == pytest.approx(3.0)
        assert "mean=3.00" in result.description
    
    def test_compute_stats_empty(self):
        calc = pymylib.Calculator()
        with pytest.raises(ValueError):
            calc.compute_stats([])
    
    def test_version(self):
        assert pymylib.Calculator.version() == "1.0.0"


class TestResult:
    def test_result_creation(self):
        result = pymylib.Result(42.0, "test description")
        assert result.value == 42.0
        assert result.description == "test description"
    
    def test_result_repr(self):
        result = pymylib.Result(42.0, "test")
        repr_str = repr(result)
        assert "42.0" in repr_str
        assert "test" in repr_str


if __name__ == "__main__":
    pytest.main([__file__, "-v"])
