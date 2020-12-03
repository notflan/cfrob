

.PHONY: test
test: test/test

test/test: test/test.cpp
	$(CXX) -I. --std=c++20 -Wall -pedantic $< -o $@
	if strings $@ | grep Hello; then exit 1; fi
	./$@
	strings $@ | grep bOFFE >> /dev/null
	@echo ""
	@echo "Passed."

clean:
	rm -f test/test
