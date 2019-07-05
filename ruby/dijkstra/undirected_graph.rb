class UndirectedGraph

  attr_reader :paths

  def initialize
    @paths = {}
  end

  def add_path(from, to, cost)
    get_paths(from)[to] = cost
  end

  def get_paths(from)
    @paths[from] ||= {}
  end

  def get_random_path
    return nil unless @paths.keys.size > 0

    get_paths(@paths.keys.sample)
  end

end
