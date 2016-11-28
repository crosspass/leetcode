require 'rest-client'
require 'json'
require 'pry'

class T

  INITVALUE = 1200

  def initialize(r)
    @weekdays = Hash.new { |h, k| h[k] = [] }
    @key = get_key
    @r = r
  end

  def get_key
    res = JSON.parse(RestClient.get 'http://pg.wutj.info/tom-home/game.php?action=newgame')
    res['key']
  end

  def url(predict)
    "http://pg.wutj.info/tom-home/predict.php?key=#{@key}&predict=#{predict}"
  end


  def getPredict(day)
    return INITVALUE if @weekdays[day].size == 0
    start = ( @weekdays[day].size / 50 ) * 50
    array = @weekdays[day][start..-1].sort
    return INITVALUE if array.empty?
    array[array.size / 2] - @r
    #array.reduce(&:+) / array.size - @r
  end

  def go
    puts @key, @r
    1000.times do |i|
      day = i % 7
      predict = getPredict(day)
      res = JSON.parse(RestClient.get url(predict))
      @weekdays[day] = @weekdays[day] << res['true_time']
    end

    res = JSON.parse(RestClient.get "http://pg.wutj.info/tom-home/game.php?action=stat&key=#{@key}").tap {|res| puts res }
    res.merge!({random: @r})
    res
  end
end

(2..6).each do |i|
  res = []
  t = T.new(i*3)
  res << t.go
  puts res
end

# 目前测试的最高分为便宜量为9 key=wf2ndf score=12700
