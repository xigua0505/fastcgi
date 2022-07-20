## 搭建流程



###  spawn-fcgi（fastcgi进程管理器）

apt install spawn-fcgi

apt install libfcgi-dev



### fastcgi（快速通用网关接口）

apt install libfcgi-dev



###  数据库

apt install sqlite3-dev

apt install sqllite3



### Nginx配置

                fastcgi_pass 127.0.0.1:9000;
                fastcgi_index index.cgi;
                include fastcgi.conf;



### 定时脚本

// 分析nginx access.log存库

access_status.sh





## 启动



### 编译连接

make build

### 启用spawn-fcgi

make start

