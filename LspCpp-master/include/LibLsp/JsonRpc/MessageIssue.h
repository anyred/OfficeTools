#pragma once
#include <string>
#include <functional>
#include <vector>
namespace lsp
{
	class Log
	{
	public:
		virtual ~Log() = default;

		enum class Level
		{
			/**
			  * OFF is a special level that can be used to turn off logging.
				特殊级别,关闭日志记录
			  */
			OFF = 1,

			/**
			 * SEVERE is a message level indicating a serious failure.
			 * <p>
			 * In general SEVERE messages should describe events that are
			 * of considerable importance and which will prevent normal
			 * program execution.   They should be reasonably intelligible
			 * to end users and to system administrators.
			 严重的消息
			 */
			 SEVERE = 2,

			 /**
			  * WARNING is a message level indicating a potential problem.
			  * <p>
			  * In general WARNING messages should describe events that will
			  * be of interest to end users or system managers, or which
			  * indicate potential problems.
				 警告级别的消息
			  *
			  */
			  WARNING = 3,
			  /**
			 * INFO is a message level for informational messages.
			 * <p>
			 * Typically INFO messages will be written to the console
			 * or its equivalent.  So the INFO level should only be
			 * used for reasonably significant messages that will
			 * make sense to end users and system administrators.
			 信息级别的消息
			 */
			 INFO = 3,
			 /**
			 * CONFIG is a message level for static configuration messages.
			 * <p>
			 * CONFIG messages are intended to provide a variety of static
			 * configuration information, to assist in debugging problems
			 * that may be associated with particular configurations.
			 * For example, CONFIG message might include the CPU type,
			 * the graphics depth, the GUI look-and-feel, etc.
			 * This level is initialized to <CODE>4</CODE>.
			 * 配置级别的消息
			 */

			 CONFIG = 4,



			 /**
			  * FINE is a message level providing tracing information.
			  * <p>
			  * All of FINE, FINER, and FINEST are intended for relatively
			  * detailed tracing.  The exact meaning of the three levels will
			  * vary between subsystems, but in general, FINEST should be used
			  * for the most voluminous detailed output, FINER for somewhat
			  * less detailed output, and FINE for the  lowest volume (and
			  * most important) messages.
			  * <p>
			  * In general the FINE level should be used for information
			  * that will be broadly interesting to developers who do not have
			  * a specialized interest in the specific subsystem.
			  * <p>
			  * FINE messages might include things like minor (recoverable)
			  * failures.  Issues indicating potential performance problems
			  * are also worth logging as FINE.
			  * This level is initialized to <CODE>5</CODE>.
				* 跟踪级别的消息
			  */
			  FINE = 5,

			  /**
			  * FINER indicates a fairly detailed tracing message.
				* 详细的跟踪消息
			  * By default logging calls for entering, returning, or throwing
			  * an exception are traced at this level.
			  * This level is initialized to <CODE>400</CODE>.
			  */
			  FINER = 6,

			  /**
			   * FINEST indicates a highly detailed tracing message.
			   * This level is initialized to <CODE>300</CODE>.
				 * 非常详细的跟踪消息
			   */
			   FINEST = 7,

			   /**
				* ALL indicates that all messages should be logged.
				* This level is initialized to <CODE>Integer.MIN_VALUE</CODE>.
				* 记录所有的消息
				*/
				ALL,
		};
		virtual  void log(Level level, std::wstring&& msg) = 0;
		virtual  void log(Level level, const std::wstring& msg) = 0;
		virtual  void log(Level level, std::string&& msg) = 0;
		virtual  void log(Level level, const std::string& msg) = 0;
		
		void  info(const std::string& msg)
		{
			log(Level::INFO, msg);
		}
		void  info(const std::wstring& msg)
		{
			log(Level::INFO, msg);
		}
		void  error(const std::string& msg)
		{
			log(Level::SEVERE, msg);
		}
		void  error(const std::wstring& msg)
		{
			log(Level::SEVERE, msg);
		}
		void  warning(const std::string& msg)
		{
			log(Level::WARNING, msg);
		}
		void  warning(const std::wstring& msg)
		{
			log(Level::WARNING, msg);
		}
	};
}

class MessageIssue {

public:
	std::string text;

	lsp::Log::Level code;

	MessageIssue(const std::string& text, lsp::Log::Level code) :text(text), code(code)
	{


	}
	MessageIssue(std::string&& text, lsp::Log::Level code) :text(text), code(code)
	{


	}


	std::string getText() {
		return text;
	}

	lsp::Log::Level getIssueCode() {
		return code;
	}


	std::string toString() {
		return getText();
	}

};
class  MessageIssueHandler
{
public:
	/**
	 * Handle issues found while parsing or validating a message. The list of issues must not be empty.
	 */
	virtual  ~MessageIssueHandler() = default;
	
	virtual  void handle(std::vector<MessageIssue>&&) = 0;
	virtual  void handle( MessageIssue&&) = 0;
};
