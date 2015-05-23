SRC_DIR=src

gen_lexer:
	(cd $(SRC_DIR); ./gen_lexer.sh)

gen_token_type:
	(cd $(SRC_DIR); ./gen_token_type.rb)

build:
	(cd $(SRC_DIR); make build)

gtest_build:
	(cd $(SRC_DIR); IS_GTEST=yes GTEST_DIR=/Users/shuochen/workspace/gtest make build)

clean:
	(cd $(SRC_DIR); make clean)
