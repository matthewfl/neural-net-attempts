class Net
  attr_reader :size, :layers
  def initialize(size)
    @size = size
    @layers = Array.new(size.size) { |i| # layers
      Array.new (size[i]) do # Neurons
        Array.new (size[i+1] || 0) do # weights
          rand
        end
      end
    }
    @values = Array.new(size.size) {|i| 
      Array.new (size[i]) { 0 }
    }
    @bias = Array.new (size.size) { |i| 
      Array.new (size[i]) { rand }
    }
  end
  
  def _Sigmoid (v) 
    return 1/(1+Math.exp(v))
  end
  
  def _DSigmoid (v) 
    return _Sigmoid(v) - (1- _Sigmoid(v))
  end
  
  def _load (data)
    throw "input data wrong size" if data.size != @values[0].size
    data.each_index { |i| 
      @values[0][i] = data[i]
    }
  end

  def _reset
    @values.each_index { |a|
      @values[a].each_index { |b| @values[a][b] = @bias[a][b] }
    }
  end

  def run (data) 
    _reset
    _load(data)
    
    on = 0
    while on < size.size - 1 do
      @layers[on].each_index do |nodeI|
        value = _Sigmoid @values[on][nodeI]
        @layers[on][nodeI].each_index do |weightI|
          @values[on+1][weightI] += @layers[on][nodeI][weightI] * value
        end
      end
      
      on += 1
    end
    return @values[-1]
  end
  
  def endError (target)
    throw "wrone number of target values" if target.size != @values[-1].size
    @totalError = 0
    @error = Array.new (@size.size) { |i| Array.new(size[i]) { 0 } }
    target.each_index
  end

  def backPropError 
    
  end

  def teach (data)
    data.each do |d|
      run d[0]
      endError d[1]
      backPropError
    end
  end
  
end


def main
  net = Net.new([3,3,2,1])
  net.teach ([
             [[0,0,0],[0]],
             [[0,0,1],[1]],
             [[0,1,0],[1]],
             [[0,1,1],[0]],
             [[1,0,0],[1]],
             [[1,0,1],[0]],
             [[1,1,0],[0]],
             [[1,1,1],[1]],
            ])
  
end

main
