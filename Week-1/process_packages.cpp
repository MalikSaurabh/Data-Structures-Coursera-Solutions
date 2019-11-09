#include <iostream>
#include <queue>
#include <vector>

struct Request 
{
    Request(int at, int pt):
        at(at),
        pt(pt)
    {}

    int at;
    int pt;
};

struct Response 
{
    Response(bool dropped, int st):
        dropped(dropped),
        st(st)
    {}

    bool dropped;
    int st;
};

class Buffer 
{
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    Response Process(const Request &request) 
    {
		while (!finish_time_.empty()) 
        {
            if (finish_time_.front() <= request.at)
                finish_time_.pop();
            else
                break;
		}
		
		if (finish_time_.size() == size_)
            return Response(true, -1);
		
		if (finish_time_.empty())
        {
            finish_time_.push(request.at + request.pt);
            return Response(false, request.at);
		}
		
		int last_element = finish_time_.back();
        finish_time_.push(last_element + request.pt);
        return Response(false, last_element);
    }
private:
    int size_;
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() 
{
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) 
    {
        int at, pt;
        std::cin >> at >> pt;
        requests.push_back(Request(at, pt));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) 
{
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) 
{
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].st) << std::endl;
}

int main() 
{
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}