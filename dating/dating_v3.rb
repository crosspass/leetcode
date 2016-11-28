#encoding: utf-8

require 'net/https'
require 'net/smtp'
require 'json'
require 'cgi'

module DOC_DATING
  CURRENT_DIR = Dir.pwd

  DOCTORS = [
    {
      name: '熊琴',
      dept_id: '0401',
      doctor_id: 9119
    },
    {
      name: '张泓',
      dept_id: '0401',
      doctor_id: 9122
    },
    {
      name: '赵慧贞',
      dept_id: '0401',
      doctor_id: 9124
    },
    {
      name: '付艳',
      dept_id: '0401',
      doctor_id: 9112
    },
    {
      name: '谢若欣',
      dept_id: '0401',
      doctor_id: 9118
    },
    {
      name: '梁晓红',
      dept_id: '0401',
      doctor_id: 9113
    },
    {
      name: '吴红媛',
      dept_id: '0401',
      doctor_id: 9117
    },
    {
      name: '张露',
      dept_id: '0401',
      doctor_id: 9121
    },
    {
      name: '张筱佼',
      dept_id: '0401',
      doctor_id: 9123
    },
  ]

  USER = {
    username: env.username,
    password: env.password,
    card_id: 233663,
  }

  NOTIFY_EMAIL = "329176418@qq.com"

  # 调试用的代理端口
  PROXY_HOST = '127.0.0.1'
  PROXY_PORT = 8888

  def code
    printf "Enter verify code in picture #{CURRENT_DIR}/code.jpg\n"
    code = gets
    code.chomp()
  end

  def login
    uri = URI('https://www.zhyygh.cn')
    cookie =
      Net::HTTP.start(uri.host, uri.port, :use_ssl => uri.scheme == 'https') do |http|
        res = http.get('/getVerifyCode')
        _cookie = {'Cookie' => res['Set-cookie'].split(';')[0]}
        open("#{CURRENT_DIR}/code.jpg", "wb") do |f|
          f.write(res.body)
        end

        open("#{CURRENT_DIR}/session.log", "wb") do |f|
          f.write(_cookie)
        end

        res = http.post('/loginAction',"JsonParms=%7B%22mode%22%3A1%2C%22username%22%3A%22#{USER[:username]}%22%2C%22password%22%3A%22#{USER[:password]}%22%2C%22verifycode%22%3A%22#{code}%22%7D", _cookie)
        # puts "Body = #{res.body}"
        if res.body.match(/"success": false/)
          puts res.body
          exit
        end
        _cookie
      end
    return cookie
  end


  def cookie(_login = true)
    if _login
      cookie = login()
    else
      cookie =
        open("#{CURRENT_DIR}/session.log", "r") do |f|
          eval(f.read())
        end
    end
  end

  def dating(_login = true)
    _cookie = cookie(_login)
    flag = false #success or failed
    #Process.daemon
    loop do
      begin
        #Net::HTTP.new('www.zhyygh.cn',nil, PROXY_HOST, PROXY_PORT).start do |http|
        uri = URI('https://www.zhyygh.cn')
        Net::HTTP.start(uri.host, uri.port, :use_ssl => uri.scheme == 'https') do |http|
          # 查询排班
          puts 'start query dating...'
          workids=[]
          DOCTORS.each do |doctor|
            # res = http.get("/web/doctor.jsp?doctor_id=#{doctor_id}", _cookie)
            # workids.push(res.body.scan(/name="workId" value="(\d+)"/))
            params = {
              'ClassName' => 'tyhx.hospool.web.action.DoctorPageAction',
              'MethodName' => 'getWorks',
              'JsonParms' => {
                'doctorId' => doctor[:doctor_id],
                'deptCode' => doctor[:dept_id]
              }.to_json
            }
            # puts params
            str = URI::encode_www_form(params)
            res = http.post("/servlet/WebRemoteCall", str,  _cookie)
            res = JSON.parse(res.body)
            next unless res['callReturn']['success']
            # puts res
            index = []
            keys = %w(morning noon noonWorks night)
            # res['callReturn']['data']['weekDay'].each_with_index{|v, i| index << i if v=~/星期六|星期日/}
            res['callReturn']['data']['weekDay'].each_with_index{|v, i| index << i if v=~/星期日/}
            # puts 'index_ids' + index.to_s
            keys.each do |key|
              res['callReturn']['data'][key].values_at(*index).flatten.each do |h|
                workids << h['id'] if h['availableCount'] > 0
              end
            end
          end
          workids.flatten!

          workids.each do |workid|
            res = http.post('/servlet/WebRemoteCall', "ClassName=tyhx.hospool.web.action.OrderPageAction&MethodName=submitOrder&JsonParms=%7B%22workId%22%3A#{workid}%2C%22cardId%22%3A#{USER[:card_id]}%2C%22orderNumber%22%3Anull%7D", _cookie)
            if res.body.match(/"success": true/)
              log(res.body)
              send_email
              exit
            end
          end
        end
        sleep(3)
      rescue StandardError => bang
        log(bang)
        next
      end
    end
  end

  $file = open("#{CURRENT_DIR}/dating.log", "a")
  def log(data)
    $file.write("\n#{Time.now}:    #{data}")
  end

  def send_email
    message = <<EOF
From: doc_dating <doc_dating@163.com>
To: A Test User <#{NOTIFY_EMAIL}>
Subject: dating sucessful

#{USER[:username]} dating success, please login your account and check!
EOF
    mail(message)
  end

  private

  def mail(message)
    Net::SMTP.start('smtp.qq.com', 587, 'smtp.qq.com', env.email, env.email_password) do |smtp|
      binding.pry
      smtp.send_message(message,'329176418@qq.com', ["#{NOTIFY_EMAIL}"])
    end
  end
end


if __FILE__ == $0
  include DOC_DATING
  if $*.include? '-c'
    dating(login=false)
  else
    dating()
  end
end
