require 'minitest/test'

# Some helpfull functions for testing
#

# array data test
# @params {array}
# @return {nil}
def test(data)
  raise 'Data format do not supported' unless data.is_a?(Array)

end
