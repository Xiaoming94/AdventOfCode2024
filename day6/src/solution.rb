require 'ostruct'

module Solution
  Pos = Struct.new(:x, :y)

  def self.nextdirection(dir)
    nextdirection = {
      up: :right,
      right: :down,
      down: :left,
      left: :up
    }
    nextdirection[dir]
  end

  class RicochetGuardGame
    attr_reader(:guard, :map)

    def initialize(gamemap_string)
      @map = GameMap.new(gamemap_string)
      @guard = Guard.new(@map.map.clone, @map.find_guard_starting_pos)
    end

    def next_step
      @guard.walk_forward
    end

    def check_game_state
      @guard.check_next_step
    end

    def reset_with_map(map)
      @guard.map = map
      @guard.reset_guard
    end
  end

  class Guard
    attr_accessor(:map)

    def initialize(map, starting_pos)
      @map = map
      @starting_pos = starting_pos
      reset_guard
    end

    def reset_guard
      @current_pos = @starting_pos.clone
      @guard_dir = :up
      @boxes = {}
    end

    def check_next_step
      (current_x, current_y) = @current_pos.to_a
      next_step = next_pos(current_x, current_y)
      return :finished if @map.key?(next_step) == false

      while @map[next_step] == :box
        return :cycle if check_cycle(next_step)

        @guard_dir = Solution.nextdirection(@guard_dir)
        next_step = next_pos(current_x, current_y)
      end
      :unfinished
    end

    def check_cycle(box_pos)
      if @boxes.key?(box_pos) && @boxes[box_pos] == @guard_dir
        true
      else
        @boxes[box_pos] = @guard_dir
        false
      end
    end

    def walk_forward
      (current_x, current_y) = @current_pos.to_a
      next_pos = next_pos(current_x, current_y)
      @map[next_pos] = :x
      @current_pos = next_pos
    end

    def calc_guard_patrol_area
      @map.values.inject(0) { |area, symb| symb == :x ? area + 1 : area }
    end

    def next_pos(current_x, current_y)
      case @guard_dir
      when :up
        Pos.new(current_x, current_y - 1)
      when :down
        Pos.new(current_x, current_y + 1)
      when :left
        Pos.new(current_x - 1, current_y)
      when :right
        Pos.new(current_x + 1, current_y)
      end
    end

    private :next_pos
  end

  class GameMap
    attr_reader :map

    def initialize(map_string)
      @map = {}
      maplines = map_string.split("\n")
      (0...maplines.size).zip(maplines).each do |y, line|
        parse_line(line, y)
      end
    end

    def parse_line(line, y_pos)
      (0...line.length).zip(line.split('')).each do |x_pos, c|
        current_pos = Pos.new(x_pos, y_pos)
        @map.merge!({ current_pos => :box }) if c == '#'
        @map.merge!({ current_pos => :dot }) if c == '.'
        @map.merge!({ current_pos => :x }) if c == '^'
      end
    end

    def find_guard_starting_pos
      @map.each do |(pos, symb)|
        next unless symb == :x

        return pos
      end
      Pos.new(0, 0)
    end

    def with_new_box_at(pos)
      new_map = @map.clone
      new_map[pos] = :box
      new_map
    end
  end

  def count_guard_steps(input)
    game = RicochetGuardGame.new(input)
    game.next_step while game.check_game_state == :unfinished
    game.guard.calc_guard_patrol_area
  end

  def find_possible_cycles(input)
    game = RicochetGuardGame.new(input)
    possible_box = 0
    game.map.map.each_key do |pos|
      next if game.map.map[pos] == :box || game.map.map[pos] == :x

      game.reset_with_map(game.map.with_new_box_at(pos))
      game_state = :unfinished
      while game_state == :unfinished
        game.next_step
        game_state = game.check_game_state
      end
      possible_box += 1 if game_state == :cycle
    end
    possible_box
  end

  module_function :count_guard_steps, :find_possible_cycles
end
