# 1. Aşama: Derleme Ortamı (Build Stage)
FROM ubuntu:22.04 AS builder

# Sistem bağımlılıklarını yükle
RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    unzip \
    && rm -rf /var/lib/apt/lists/*

# Eigen kütüphanesini kur (Mühendislik standardı)
WORKDIR /dependencies
RUN wget https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip && \
    unzip eigen-3.4.0.zip && \
    mv eigen-3.4.0/Eigen /usr/local/include/Eigen && \
    rm -rf eigen-3.4.0*

# Proje dosyalarını kopyala ve derle
WORKDIR /app
COPY . .
RUN g++ -I . -I /usr/local/include/Eigen main.cpp -o MatFuse_Sim

# 2. Aşama: Çalışma Ortamı (Runtime Stage)
FROM ubuntu:22.04
WORKDIR /app
COPY --from=builder /app/MatFuse_Sim .

# Simülasyonu başlat
CMD ["./MatFuse_Sim"]