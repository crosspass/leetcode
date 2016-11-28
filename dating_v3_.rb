#encoding: utf-8

require 'net/https'
require 'net/smtp'
require 'json'
require 'cgi'

module DOC_DATING
  CURRENT_DIR = Dir.pwd
  DOCTORS = [
    {
      name: '尹保民',
      dept_id: '1201',
      doctor_id: 9222
    },
    {
      name: '段嫦丽',
      dept_id: '1201',
      doctor_id: 9194
    },
    {
      name: '金丰梅',
      dept_id: '1201',
      doctor_id: 9199
    },
    {
      name: '李继红',
      dept_id: '1201',
      doctor_id: 9201
    },
    {
      name: '林道彬',
      dept_id: '1201',
      doctor_id: 9203
    },
    {
      name: '刘俐',
      dept_id: '1201',
      doctor_id: 9205
    },
    {
      name: '文慧',
      dept_id: '1201',
      doctor_id: 9216
    },
    {
      name: '杨小红',
      dept_id: '1201',
      doctor_id: 9220
    }
  ]

  USER = {
    username: 'test',
    password: 'test',
    card_id: 666666,
  }

  NOTIFY_EMAIL = "wyc03_21@163.com"

  # 调试用的代理端口
  PROXY_HOST = '127.0.0.1'
  PROXY_PORT = 8888

  def code
    printf "Enter verify code in path #{CURRENT_DIR}/code.jpg\n"
    code = gets
    code
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

        _code = code().chomp()
        res = http.post('/loginAction',"JsonParms=%7B%22mode%22%3A1%2C%22username%22%3A%22#{USER[:username]}%22%2C%22password%22%3A%22#{USER[:password]}%22%2C%22verifycode%22%3A%22#{_code}%22%7D", _cookie)
        # puts "Body = #{res.body}"
        exit if res.body.match(/"success": false/)
        _cookie
      end
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
    old_workids = []
    flag = false #success or failed
    cardid = ''
    #Process.daemon
    loop do
      begin
        #Net::HTTP.new('www.zhyygh.cn',nil, PROXY_HOST, PROXY_PORT).start do |http|
        uri = URI('https://www.zhyygh.cn')
        Net::HTTP.start(uri.host, uri.port, :use_ssl => uri.scheme == 'https') do |http|
          # 获取医生ID
          res=""
          doctor_ids=[]
          #查询排班
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
            res['callReturn']['data']['weekDay'].each_with_index{|v, i| index << i if v=~/星期六|星期日/}
            # puts 'index_ids' + index.to_s
            keys.each do |key|
              res['callReturn']['data'][key].values_at(*index).flatten.each do |h|
                workids << h['id'] if h['availableCount'] > 0
              end
            end
          end
          # puts 'workids' + workids.to_s
          workids.flatten!

          # 获取提交用的cardid
          # cardid ||= res.body.scan(/option value='(\d+)'/).last.last
          workids.each do |workid|
            res = http.post('/servlet/WebRemoteCall', "ClassName=tyhx.hospool.web.action.OrderPageAction&MethodName=submitOrder&JsonParms=%7B%22workId%22%3A#{workid}%2C%22cardId%22%3A#{USER[:card_id]}%2C%22orderNumber%22%3Anull%7D", _cookie)
            flag = true  if res.body.match(/"success": true/)
            if res.body.force_encoding('utf-8').match(/超时/)
              log(res.body)
              warn_email
            end
          end
          if flag
            log(flag)
            send_email
            exit
          end
        end
        sleep(3)
      rescue StandardError => bang
        log("#{Time.now}")
        log(bang)
        exit
      end
    end
  end

  def log(data)
    open("#{CURRENT_DIR}/dating.log", "a") do |f|
      f.write("\n")
      f.write(Time.now)
      f.write(data)
    end
  end

  def send_email
    message = <<EOF
From: doc_dating <doc_dating@163.com>
To: A Test User <#{NOTIFY_EMAIL}>
Subject: dating sucessful

#{USER[:username]} dating success, please login your account and check!
EOF

    Net::SMTP.start('smtp.163.com', 25, 'smtp.163.com', 'doc_dating@163.com', 'doc__dating', :plain) do |smtp|
      smtp.send_message(message,'doc_dating@163.com', ["#{NOTIFY_EMAIL}"])
    end
  end

  def warn_email
    message = <<EOF
From: doc_dating <doc_dating@163.com>
To: A Test User <#{NOTIFY_EMAIL}>
Subject: login timeout

#{USER[:username]} login timeout, please login again!
EOF

    Net::SMTP.start('smtp.163.com', 25, 'smtp.163.com', 'doc_dating@163.com', 'doc__dating', :plain) do |smtp|
      smtp.send_message(message,'doc_dating@163.com', ["#{NOTIFY_EMAIL}"])
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
